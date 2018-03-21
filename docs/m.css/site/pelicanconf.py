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

import shutil
import logging

AUTHOR = 'Vladimír Vondruš'

M_SITE_LOGO_TEXT = 'm.css'

SITENAME = 'm.css'
SITEURL = ''

STATIC_URL = '{path}'

PATH = 'content'
ARTICLE_PATHS = ['examples']
ARTICLE_EXCLUDES = ['examples/authors', 'examples/categories', 'examples/tags']
PAGE_PATHS = ['']

TIMEZONE = 'Europe/Prague'

DEFAULT_LANG = 'en'

import platform
if platform.system() == 'Windows':
    DATE_FORMATS = {'en': ('usa', '%b %d, %Y')}
else:
    DATE_FORMATS = {'en': ('en_US.UTF-8', '%b %d, %Y')}

# Feed generation is usually not desired when developing
FEED_ATOM = None
FEED_ALL_ATOM = None
CATEGORY_FEED_ATOM = None
TRANSLATION_FEED_ATOM = None
AUTHOR_FEED_ATOM = None
AUTHOR_FEED_RSS = None

M_BLOG_NAME = "m.css example articles"
M_BLOG_URL = 'examples/'

M_FAVICON = ('favicon.ico', 'image/x-icon')

M_SOCIAL_TWITTER_SITE = '@czmosra'
M_SOCIAL_TWITTER_SITE_ID = 1537427036
M_SOCIAL_IMAGE = 'static/site.jpg'
M_SOCIAL_BLOG_SUMMARY = 'Example articles for the m.css Pelican theme'

M_METADATA_AUTHOR_PATH = 'examples/authors'
M_METADATA_CATEGORY_PATH = 'examples/categories'
M_METADATA_TAG_PATH = 'examples/tags'

M_LINKS_NAVBAR1 = [('Why?', 'why/', 'why', []),
                   ('CSS', 'css/', 'css', [
                        ('Grid system', 'css/grid/', 'css/grid'),
                        ('Typography', 'css/typography/', 'css/typography'),
                        ('Components', 'css/components/', 'css/components'),
                        ('Page layout', 'css/page-layout/', 'css/page-layout'),
                        ('Themes', 'css/themes/', 'css/themes')]),
                   ('Pelican', 'pelican/', 'pelican', [
                        ('Writing content', 'pelican/writing-content/', 'pelican/writing-content'),
                        ('Theme', 'pelican/theme/', 'pelican/theme')])]

M_LINKS_NAVBAR2 = [('Pelican plugins', 'plugins/', 'plugins', [
                        ('HTML sanity', 'plugins/htmlsanity/', 'plugins/htmlsanity'),
                        ('Components', 'plugins/components/', 'plugins/components'),
                        ('Images', 'plugins/images/', 'plugins/images'),
                        ('Math and code', 'plugins/math-and-code/', 'plugins/math-and-code'),
                        ('Links', 'plugins/links/', 'plugins/links'),
                        ('Metadata', 'plugins/metadata/', 'plugins/metadata')]),
                   ('Doxygen theme', 'doxygen/', 'doxygen', []),
                   ('GitHub', 'https://github.com/mosra/m.css', '', [])]

M_LINKS_FOOTER1 = [('m.css', '/'),
                   ('Why?', 'why/'),
                   ('GitHub', 'https://github.com/mosra/m.css'),
                   ('Gitter', 'https://gitter.im/mosra/m.css'),
                   ('E-mail', 'mailto:mosra@centrum.cz'),
                   ('Twitter', 'https://twitter.com/czmosra'),
                   ('Build Status', 'build-status/')]

M_LINKS_FOOTER2 = [('CSS', 'css/'),
                   ('Grid system', 'css/grid/'),
                   ('Typography', 'css/typography/'),
                   ('Components', 'css/components/'),
                   ('Page layout', 'css/page-layout/'),
                   ('Themes', 'css/themes/')]

M_LINKS_FOOTER3 = [('Pelican', 'pelican/'),
                   ('Writing content', 'pelican/writing-content/'),
                   ('Theme', 'pelican/theme/'),
                   ('', ''),
                   ('Doxygen theme', 'doxygen/')]

M_LINKS_FOOTER4 = [('Pelican plugins', 'plugins/'),
                   ('HTML sanity', 'plugins/htmlsanity/'),
                   ('Components', 'plugins/components/'),
                   ('Images', 'plugins/images/'),
                   ('Math and code', 'plugins/math-and-code/'),
                   ('Links', 'plugins/links/'),
                   ('Metadata', 'plugins/metadata/')]

M_FINE_PRINT = """
| m.css. Copyright © `Vladimír Vondruš <http://mosra.cz>`_, 2017--2018. Site
  powered by `Pelican <https://getpelican.com>`_ and m.css.
| Code and content is `available on GitHub under MIT <https://github.com/mosra/m.css>`_.
  Contact the author via `Gitter <https://gitter.im/mosra/m.css>`_,
  `e-mail <mosra@centrum.cz>`_ or `Twitter <https://twitter.com/czmosra>`_.
"""

DEFAULT_PAGINATION = 10

STATIC_PATHS = ['static']
EXTRA_PATH_METADATA = {'static/favicon.ico': {'path': 'favicon.ico'}}

PLUGIN_PATHS = ['../pelican-plugins']
PLUGINS = ['m.abbr',
           'm.code',
           'm.components',
           'm.dox',
           'm.filesize',
           'm.gl',
           'm.gh',
           'm.htmlsanity',
           'm.images',
           'm.math',
           'm.metadata']

THEME = '../pelican-theme'
THEME_STATIC_DIR = 'static'
M_THEME_COLOR = '#22272e'
M_CSS_FILES = ['https://fonts.googleapis.com/css?family=Source+Code+Pro:400,400i,600%7CSource+Sans+Pro:400,400i,600,600i&subset=latin-ext',
               'static/m-dark.css',
              #'static/m-debug.css'
              ]
#M_CSS_FILES = ['https://fonts.googleapis.com/css?family=Libre+Baskerville:400,400i,700,700i%7CSource+Code+Pro:400,400i,600',
               #'static/m-light.css']

FORMATTED_FIELDS = ['summary', 'landing', 'header', 'footer', 'description', 'badge']

M_HTMLSANITY_SMART_QUOTES = True
M_HTMLSANITY_HYPHENATION = True
M_DOX_TAGFILES = [
    ('../doc/doxygen/corrade.tag', 'http://doc.magnum.graphics/corrade/', ['Corrade::'])]

if not shutil.which('latex'):
    logging.warning("LaTeX not found, fallback to rendering math as code")
    M_MATH_RENDER_AS_CODE = True

DIRECT_TEMPLATES = ['archives']

PAGE_URL = '{slug}/'
PAGE_SAVE_AS = '{slug}/index.html'
ARCHIVES_URL = 'examples/'
ARCHIVES_SAVE_AS = 'examples/index.html'
ARTICLE_URL = '{slug}/' # category is part of the slug (i.e., examples)
ARTICLE_SAVE_AS = '{slug}/index.html'
AUTHOR_URL = 'author/{slug}/'
AUTHOR_SAVE_AS = 'author/{slug}/index.html'
CATEGORY_URL = 'category/{slug}/'
CATEGORY_SAVE_AS = 'category/{slug}/index.html'
TAG_URL = 'tag/{slug}/'
TAG_SAVE_AS = 'tag/{slug}/index.html'

AUTHORS_SAVE_AS = None # Not used
CATEGORIES_SAVE_AS = None # Not used
TAGS_SAVE_AS = None # Not used

SLUGIFY_SOURCE = 'basename'
PATH_METADATA = '(?P<slug>.+).rst'
