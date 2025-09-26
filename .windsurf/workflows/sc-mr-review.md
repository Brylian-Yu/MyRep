---
description: Do code review for a specific merge request with specific rules to find out if any problem
auto_execution_mode: 1
---

1. search the comments on the selected merge request ID, check if I have reviewed and comment it within 2 hours
The reviewed comment has a "[windsurf review]" string in its overall comment.

2. If the selected merge request has been reviewed by me within 2 hours, then goto step-12 directly

3. for the selected merge request ID, get its project name.

4. The source code of this project is located in the current directory. The name of the root directory of the source code is consistent with the project name.

5. If source code is found, read and understand the source code deeply on: 
    - directory structure
    - code module function
    - compilation construction process
    - program operation mechanism  

6. If source code is found, read all merged MRs history to enhance the understanding of the source code

7. for the selected merge request, according to rule **sc-code-check-cwe-top25-rule**, check if all code diffs comply with it
    - 7.1 list all diff files
    - 7.2 for each diff file, check the code rule:
    -- 7.2.1 if there is any problem, show the detailed analysis 
    -- 7.2.2 if no problem, show PASS

8. for the selected merge request, according to rule **sc-code-check-owasp-top10-rule**, check if all code diffs comply with it
    - 8.1 list all diff files
    - 8.2 for each diff file, check the code rule:
    -- 8.2.1 if there is any problem, show the detailed analysis 
    -- 8.2.2 if no problem, show PASS

9. for the selected merge request, according to rule **sc-code-check-sercomm-rule**, check if all code diffs comply with it
    - 9.1 list all diff files
    - 9.2 for each diff file, check the code rule:
    -- 9.2.1 if there is any problem, show the detailed analysis 
    -- 9.2.2 if no problem, show PASS

10. for the selected merge request, according to rule **sc-code-check-reserved-rule**, check if all code diffs comply with it
    - 10.1 list all diff files
    - 10.2 for each diff file, check the code rule:
    -- 10.2.1 if there is any problem, show the detailed analysis 
    -- 10.2.2 if no problem, show PASS

11. after all reviews done, feedback the review analysis comments and post them to gitlab MR page
    - 11.1 (mandatory) in MR **Overview page**, add overall comments according to rule **sc-overall-comment-format-rule**
    - 11.2 (mandatory) in MR **Changes page**, use GitLab **discussions API** to add **high and medium priority** inline comments **anchored to specific diff files precisely**, according to rule **sc-inline-comment-format-rule**

12. end