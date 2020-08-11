# Contributing to Madd2

First, thank you for your interest in contributing to Madd! :tada:

The following is a set of guidelines we follow to ensure the quality and organization of work being added to the project. These are guidelines, not rules, and best judgement should be used when interpreting them. Don't like something in here? Feel free to propose changes in a pull request.

## How Can I Contribute?

### Bug Hunting :bug:
This section guides you through the bug reporting process. Following these guidelines should help maintainers understand your report, reproduce the behavior, and hopefully work towards a fix. Madd2 uses [Github Issues](https://github.com/realliance/madd2/issues) to track outstanding bugs.

Before creating a bug report, please check to see if [a similar issue has already been posted.](https://github.com/realliance/madd2/labels/bug) If it has **and is still open,** add a comment instead of creating a new issue. This helps us gauge the impact of the problem in one filing.

If you find a Closed issue similar to your bug, open a new issue and link the original issue within the description.

When submitting a bug report, please use the bug report issue template and fill out all sections the best you can.

### Suggesting Enhancements :memo:
This section guides through the enhancement suggestion process. Madd2 uses [Github Issues](https://github.com/realliance/madd2/issues) to track these suggestions.

Before creating a suggestion, please check to see if a similar enchantment has [already been posted](https://github.com/realliance/madd2/labels/enhancement). If it has, add a comment instead of creating a new suggestion.

When submitting a suggestion, please use the enhancement suggestion issue template and fill out all sections the best you can.

### Your First Code Contributions :apple:
Unsure where to start? You could start be looking through the `good first issue` and `help wanted` issues:

- [Good First Issue](https://github.com/realliance/madd2/labels/good%20first%20issue) - issues that should require minimal additions to complete. A good place to start when getting used to the project codebase/open source ecosystem.
- [Help Wanted Issue](https://github.com/realliance/madd2/labels/help%20wanted) - issues that are a bit more involved than `good first issue` issues, but are in need of additional help.

### Pull Requests :fire:
This section guides you through the process of making a successful code contribution to Madd! The process has several goals:

- Maintain or improve the codebase's quality
- Fix problems that important to users
- Engage the interests of the community
- Enable a sustainable system for maintainers to review possible contributions

Please follow these steps to have your pull request considered:
1. Follow all instructions in the template
2. Follow the styleguides
3. Once submitted, verify all status checks are passing.

#### Styleguide and Linting

Our codebase roughly follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). Madd has style conforming automated via [clang-format](https://clang.llvm.org/docs/ClangFormat.html), and can be manually run using `make format` within your build environment. Ensure all additions have been formatted before submitting your pull request.

Linting is managed by [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), which can be run via `make tidy` from your build environment. For automated lint error fixing, use `make fix`. Ensure no linting errors are present before submitting your pull request.

#### Status Checks

Upon submitting your pull request or pushing a new commit to your pull request, a validation pipeline will test the following aspects of your submission:

- All code conforms to the present style guide.
- All code conforms to the present linting checks.
- Madd can be built with clang.
- All ctest unit tests pass.

#### What happens if a status check fails?

Your pull request can not be considered by maintainers unless all status checks pass. Please fix any issues in your contribution or reach out if you believe your pull request is being blocked by any outstanding bugs.

### Additional Notes

#### Issue and PR Labels

This section lists the labels we use to help track and manage issues and pull requests.

| Label Name | :mag: | Description |
| ---------- | -------- | ----------- |
| `bug` | [search](https://github.com/realliance/madd2/labels/bug) | Confirmed bug or reports that are likely to be bugs |
| `documentation` | [search](https://github.com/realliance/madd2/labels/documentation) | Improvements to any type of documentation |
| `duplicate` | [search](https://github.com/realliance/madd2/labels/duplicate) | Issues that are duplicates of others (i.e. already posted issues) |
| `enhancement` | [search](https://github.com/realliance/madd2/labels/enhancement) | Feature/Improvement requests |
| `good first issue` | [search](https://github.com/realliance/madd2/labels/good%20first%20issue) | Less complex issues that would be great first issues to work on for new contributors. |
| `help wanted` | [search](https://github.com/realliance/madd2/labels/help%20wanted) | The Madd core team would appreciate help from the community in resolving these issues |
| `invalid` | [search](https://github.com/realliance/madd2/labels/invalid) | Issues that aren't valid (e.g. user errors) |
| `more info needed` | [search](https://github.com/realliance/madd2/labels/more%20info%20needed) | More information is needed before moving forward with this issue |
| `question` | [search](https://github.com/realliance/madd2/labels/question) | Questions related to Madd development |
| `wontfix` | [search](https://github.com/realliance/madd2/labels/wontfix) | The Madd core team has decided not to fix these issues for now |
