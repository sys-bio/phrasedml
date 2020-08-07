"""
The libPhrasedml library, (c) 2014-2015 Lucian Smith, Kiri Choi, J Kyle Medley, and Herbert Sauro

libPhrasedml is a library for Phrasedml, a human-readable,
human-writeable simulation experiment definition language.
For more information, see http://phrasedml.sf.net/
"""

from .phrasedml import *
from pkg_resources import get_distribution

#__version__ = LIBPHRASEDML_VERSION_STRING[1:]
 __version__ = get_distribution('phrasedml').version

