---
description: Sync local repository with remote changes
auto_execution_mode: 3
---

1. Check current branch and working directory status
// turbo
2. Stash any uncommitted changes to preserve local work

3. Fetch latest changes from remote repository
// turbo
4. Check branch relationship with remote (ahead/behind/diverged)

5. Handle sync based on status:
   - If behind: pull changes
   - If diverged: reset hard to origin/main (WARNING: loses local commits)
   - If ahead: push local changes or reset if unwanted

6. Pop stashed changes back if any were stashed

7. Show final sync status and verify clean state
// turbo
8. List any remaining untracked or modified files that need attention