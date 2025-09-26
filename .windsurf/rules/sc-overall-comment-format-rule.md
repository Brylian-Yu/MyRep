---
trigger: always_on
---

# Rule: sc-overall-comment-format-rule

Overall comment format specification

## Overall Comment Format Structure

### 1. Title
**Format**: `[Windsurf Review][overall][time][result]`
**Components**:
- **time**: the time point of this comment reported
- **result**: the overall code review result
-- if no problem: "PASS"
-- else if any high or medium priority problem: "Critical"
-- else if only low priority problem: "Attention"

### 2. Modified Files Check List
List all modified files with their review status
**Format**: `filename [PASS/Partly PASS/FAILED]`
**Components**:
- PASS: no problem in this files
- Partlay PASS: only low priority problem in this files
- FAILED: any high or medium priority problem in this files

### 3. Requirement Satisfaction Analysis
**Format:**
- Requirement: by considering the title of this merge request and other relevant information, understand the purpose of the changes made in this merge request.
- Satisfaction: has the requirement been met? (YES / NO)

### 4. Problems List

#### 4.1 High prority problems
**Format**:
problem # 1
- filename
- standard: cweTop25 / owaspTop10 / sercomm / reserved
- issue name
- description of the problem
- suggestion for problem fix

problem # 2
...

#### 4.2 Medium prority problems
problem # 1
- filename
- standard: cweTop25 / owaspTop10 / sercomm / reserved
- issue name
- description of the problem
- suggestion for problem fix

problem # 2
...

#### 4.3 Low prority problems
problem # 1
- filename
- standard: cweTop25 / owaspTop10 / sercomm / reserved
- issue name
- description of the problem
- suggestion for problem fix

problem # 2
...


### 5. Reverse Test Case
Based on the understanding of this merge request, provide possible additional test cases for reverse testing
**Format:**
Case # 1
- description
- detail steps:
...

Case # 2
- description
- detail steps:
...

Case # 3
...