#
#   This file is part of m.css.
#
#   Copyright © 2017, 2018 Vladimír Vondruš <mosra@centrum.cz>
#
#   Permission is hereby granted, free of charge, to any person obtaining a
#   copy of this software and associated documentation files (the "Software"),
#   to deal in the Software without restriction, including without limitation
#   the rights to use, copy, modify, merge, publish, distribute, sublicense,
#   and/or sell copies of the Software, and to permit persons to whom the
#   Software is furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included
#   in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#   DEALINGS IN THE SOFTWARE.
#

from . import parse_link
from docutils.parsers.rst.states import Inliner
from docutils import nodes, utils
from docutils.parsers import rst
from pelican import signals
import xml.etree.ElementTree as ET
import os

import logging

logger = logging.getLogger(__name__)

symbol_mapping = {}
symbol_prefixes = ['']
tagfile_basenames = []

def init(pelicanobj):
    global symbol_mapping, symbol_prefixes, tagfile_basenames

    tagfiles = pelicanobj.settings.get('M_DOX_TAGFILES', [])

    # Pre-round to populate subclasses

    for tagfile, path, prefixes in tagfiles:
        tagfile_basenames += [(os.path.splitext(os.path.basename(tagfile))[0], path)]
        symbol_prefixes += prefixes

        tree = ET.parse(tagfile)
        root = tree.getroot()
        for child in root:
            if child.tag == 'compound' and 'kind' in child.attrib:
                # Linking to pages
                if child.attrib['kind'] == 'page':
                    link = path + child.find('filename').text + '.html'
                    symbol_mapping[child.find('name').text] = (child.find('title').text, link)

                # Linking to files
                if child.attrib['kind'] == 'file':
                    link = path + child.find('filename').text + ".html"
                    symbol_mapping[child.find('path').text + child.find('name').text] = (None, link)

                    for member in child.findall('member'):
                        if not 'kind' in member.attrib: continue

                        # Preprocessor defines and macros
                        if member.attrib['kind'] == 'define':
                            symbol_mapping[member.find('name').text + ('()' if member.find('arglist').text else '')] = (None, link + '#' + member.find('anchor').text)

                # Linking to namespaces, structs and classes
                if child.attrib['kind'] in ['class', 'struct', 'namespace']:
                    name = child.find('name').text
                    link = path + child.findtext('filename') # <filename> can be empty (cppreference tag file)
                    symbol_mapping[name] = (None, link)
                    for member in child.findall('member'):
                        if not 'kind' in member.attrib: continue

                        # Typedefs, constants
                        if member.attrib['kind'] == 'typedef' or member.attrib['kind'] == 'enumvalue':
                            symbol_mapping[name + '::' + member.find('name').text] = (None, link + '#' + member.find('anchor').text)

                        # Functions
                        if member.attrib['kind'] == 'function':
                            # <filename> can be empty (cppreference tag file)
                            symbol_mapping[name + '::' + member.find('name').text + "()"] = (None, link + '#' + member.findtext('anchor'))

                        # Enums with values
                        if member.attrib['kind'] == 'enumeration':
                            enumeration = name + '::' + member.find('name').text
                            symbol_mapping[enumeration] = (None, link + '#' + member.find('anchor').text)

                            for value in member.findall('enumvalue'):
                                symbol_mapping[enumeration + '::' + value.text] = (None, link + '#' + value.attrib['anchor'])

                # Sections
                for section in child.findall('docanchor'):
                    symbol_mapping[section.text] = (section.attrib.get('title', ''), link + '#' + section.text)

def dox(name, rawtext, text, lineno, inliner: Inliner, options={}, content=[]):
    title, target = parse_link(text)

    # Try linking to the whole docs first
    for basename, url in tagfile_basenames:
        if basename == target:
            if not title:
                # TODO: extract title from index page in the tagfile
                logger.warning("Link to main page `{}` requires a title".format(target))
                title = target

            node = nodes.reference(rawtext, title, refuri=url, **options)
            return [node], []

    for prefix in symbol_prefixes:
        if prefix + target in symbol_mapping:
            link_title, url = symbol_mapping[prefix + target]
            if title:
                use_title = title
            elif link_title:
                use_title = link_title
            else:
                if link_title is not None:
                    logger.warning("Doxygen anchor `{}` has no title, using its ID as link title".format(target))

                use_title = target
            node = nodes.reference(rawtext, use_title, refuri=url, **options)
            return [node], []

    # TODO: print file and line
    #msg = inliner.reporter.warning(
        #'Doxygen symbol %s not found' % target, line=lineno)
    #prb = inliner.problematic(rawtext, rawtext, msg)
    if title:
        logger.warning("Doxygen symbol `{}` not found, rendering just link title".format(target))
        node = nodes.inline(rawtext, title, **options)
    else:
        logger.warning("Doxygen symbol `{}` not found, rendering as monospace".format(target))
        node = nodes.literal(rawtext, target, **options)
    return [node], []

def register():
    signals.initialized.connect(init)

    rst.roles.register_local_role('dox', dox)
