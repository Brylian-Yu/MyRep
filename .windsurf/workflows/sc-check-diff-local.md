---
description: Check diff info of local reposity space
auto_execution_mode: 3
---

1. run 'git diff HEAD > review.diff' to generate the diff file

2. check the review.diff file to find the files added or modified

3. delete the latest memory 'memory_diff_local' if it exists

3. create a memory 'memory_diff_local' to save the information of files added or modified

4. force delete the review.diff file(try cmd/powershell/shell)