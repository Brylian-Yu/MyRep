---
description: Make local code review before creating new pull request
auto_execution_mode: 3
---

1. call /sc-check-diff-local to update the memory to save the diffed files info

2. if there are diffed files, then please check the code rule of them by rule 'sc-code-rule'; else stop this workflow

3. if check code rule with no problem, then make local code review by rule 'sc-local-review-rule'; else stop this workflow

4. if local code review with no problem, then create a new pull request by rule 'sc-pr-format-rule'; else stop this workflow