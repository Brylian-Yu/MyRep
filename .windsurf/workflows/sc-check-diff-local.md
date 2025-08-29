---
description: Check diff info of local reposity space
auto_execution_mode: 3
---

1. run 'git status --porcelain > review.diff' to generate the diff file
// turbo

2. check the review.diff file to find the files new/deleted/modified - if review.diff is empty, verify by running 'git status --porcelain' directly and also check 'git diff --name-only' to ensure no changes are missed

3. if review.diff shows changes, analyze each file type:
   - For modified files (M): run 'git show HEAD:[filename]' to get original content and compare with current file
   - For new files (??): note as new additions
   - For deleted files (D): note as deletions

4. delete the latest memory 'memory_diff_local' if it exists

5. create a memory 'memory_diff_local' to save the detailed information of files new/deleted/modified, including:
   - File names and status (M/??/D)
   - For modified files: specific changes made (additions/deletions)
   - Total count of diffed files

6. force delete the review.diff file(try cmd/powershell/shell)
// turbo

7. list the diff info of files new/deleted/modified with detailed change descriptions