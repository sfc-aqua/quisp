# Contributing to QuISP

Thank you for reading this page! We love your input! We want to make contributing to this project as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

When contributing to this repository, please first discuss the change you wish to make via issue, 
email, or any other method with the owners of this repository before making a change.

We recommend reaching us via [QuISP Slack team](https://aqua-quisp.slack.com).

The following is a set of guidelines, not rules. Use your best judgment, and feel free to propose change to this document via discussing with us on slack or pull request.

**Table of Contents**

[Code of Conduct](#code-of-conduct)

[I just have a question about using QuISP!](#i-just-have-a-question-about-quisp)

[What should I know before getting started?](#what-should-i-know-before-getting-started)

  + [We Develop with Github](#we-develop-with-github)
  + [We use Github Flow](#we-use-github-flow)
  + [QuISP Design Decisions](#quisp-design-decisions)

[How can I contribute?](#how-can-i-contribute)

  + [Reporting Bugs](#reporting-bugs)
  + [Pull Request Procedure](#pull-request-procedure)

[Styleguides](#styleguides)

[License](#license)

  + [Any contributions you make will be under the BSD 3-Clause License](#any-contributions-you-make-will-be-under-the-bsd-3-clause-license)

[Attribution](#attribution)

[References](#references)

## Code of Conduct

Please note we have a [code of conduct](/CODE_OF_CONDUCT.md), please follow it in all your interactions with the project. If you find unacceptable behaviour please report to us by email or slack.

## I just have a question about using QuISP!

Questions are welcome! Please don't file an issue to ask a question.
We have quite detailed [documents](/doc) regarding the functionality of QuISP. We admit that most documents are still in progress and contribution are welcome!

We also encourage you to [join our slack](https://aqua-quisp.slack.com) and ask questions there!

* Even though slack is a chat service, it can take several hours for us to respond - please be patient!
* We have channels for most of the important topics (e.g. `#links`, `#app-traffic`, `#muxing`, `#purificaton`) but if you aren't sure which channel to ask, we recommend asking in `#questions`.

## What should I know before getting started

### We Develop with Github

We use github to host code, to track issues and feature requests, as well as accept pull requests.

## We Use [Github Flow](https://guides.github.com/introduction/flow/index.html)

All code changes should happen through pull requests.

## QuISP Design Decisions

(TBD)

## How can I contribute?

### Reporting Bugs

Report bugs using Github's [issues](https://github.com/sfc-aqua/quisp/issues)

We use GitHub issues to track public bugs. Report a bug by [opening a new issue](https://github.com/sfc-aqua/quisp/issues/new/choose); it's that easy!

**Write bug reports with detail, background, and sample code**

Great bug reports tend to have:

* A quick summary and/or background
* Steps to reproduce
  + Tell us what your setup is (OS, are you using local installation or docker version etc.)
  + Be specific! (give us your `.ini` file, network name, parameters setting, actions that caused the bug, etc)
  + Give sample code if you can. The report should includes sample code that *anyone* with a base QuISP setup can run to reproduce what you were seeing.
* What you expected would happen
* What actually happens (screenshots and timestamp/events# if it's deep in simulation)
* Notes (possibly including why you think this might be happening, or stuff you tried that didn't work)

People *love* thorough bug reports.

## Pull Requests Procedure

Pull requests are the best way to propose changes to the codebase (we use [Github Flow](https://guides.github.com/introduction/flow/index.html)). We actively welcome your pull requests:

1. Fork the repo and create your branch from `master`.
2. If you've added code that should be tested, add tests.
3. If you've changed APIs, update the documentation.
4. Verify that code can successfully build and simulation is working on your system.
4. Ensure the test suite passes.
5. Make sure your code lints. We treat warning from linter (`clang-tidy`) as errors (refer to [styleguides](#styleguides)).
6. Issue that pull request!

### Styleguides

We define how to format code via `.clang-format` and lint vs `.clang-tidy` at project root. We also have a script which you can use to run the formatter and linter via `$ make format` or `$ sh docker_run_lint.sh` before committing. We follow code format from [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). 

* If you're writing code using [Visual Studio Code](https://code.visualstudio.com), we have a [guide](/doc/vscode_setup.md) on how to setup.
* If you're using OMNeT++ IDE, you can format the code seamlessly using [CppStyle](https://github.com/wangzw/CppStyle).

## License

By contributing, you agree that your contributions will be licensed under [3-Clause BSD License](/LICENSE).

### Any contributions you make will be under the BSD 3-Clause License

In short, when you submit code changes, your submissions are understood to be under the same [3-Clause BSD License](/LICENSE) that covers the project. Feel free to contact the maintainers if that's a concern.

## Attribution

[QuISP website](https://aqua.sfc.wide.ad.jp/quisp_website/)

## References

This document was adapted from two open-source contribution guidelines templates [here](https://github.com/atom/atom/blob/master/CONTRIBUTING.md#pull-requests) and [here](https://gist.github.com/briandk/3d2e8b3ec8daf5a27a62).
