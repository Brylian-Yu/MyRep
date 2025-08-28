---
description: Check diff info of local reposity space
auto_execution_mode: 3
---

1. run 'git diff HEAD > review.diff' to generate the diff file

2. check the review.diff file to find the files new/deleted/modified

3. delete the latest memory 'memory_diff_local' if it exists

4. create a memory 'memory_diff_local' to save the information of files new/deleted/modified

5. force delete the review.diff file(try cmd/powershell/shell)

6. list the diff info of files new/deleted/modified