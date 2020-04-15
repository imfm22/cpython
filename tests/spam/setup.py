from distutils.core import setup, Extension

spam_module = Extension('spam', sources = ['spammodule.c'])
setup(
    name='SpamModule',
    version='1.0',
    description="Spam Module",
    ext_modules=[spam_module]
)