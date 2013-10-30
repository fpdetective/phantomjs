# [PhantomJSlog](http://phantomjs.org) - Scriptable Logging Headless WebKit

PhantomJS ([www.phantomjs.org](http://phantomjs.org)) is a headless WebKit scriptable with JavaScript or CoffeeScript. It is used by hundreds of [developers](https://github.com/ariya/phantomjs/wiki/Buzz) and dozens of [organizations](https://github.com/ariya/phantomjs/wiki/Users) for web-related development workflow.

This is a fork of PhantomJS that logs events that might be related to device fingerprinting.
Modified PhantomJS browser is used as a part of the ([FPDetective framework](https://github.com/fpdetective/fpdetective)).

The patch we used to modify PhantomJS can be found ([here](https://github.com/fpdetective/phantomjs/blob/master/patches/log-fp-events.patch)).

Read original ([PhantomJS README](https://github.com/ariya/phantomjs/blob/master/README.md)) to get more information about PhantomJS.
