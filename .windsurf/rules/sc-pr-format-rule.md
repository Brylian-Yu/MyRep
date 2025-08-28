---
trigger: always_on
---

# Rule: sc-pr-format-rule

- Pull Request format specification for standardized PR creation

## PR Format Structure

### 1. Title Format
**Format**: `[ProjectName][BranchName][JiraID][Feature|BUG|Optimization] description`

**Components**:
- **ProjectName**: Read from memory `memory-project-name`
- **BranchName**: Repository Name
- **JiraID**: Read from memory `memory-jira-id`
- **Feature|BUG|Optimization and description**: Choose according to the result of workflow `sc-code-review-local`

### 2. Modification Time
- Include the timestamp when changes were made

### 3. Modifier
- **Modifier**: Read from `git config user.name`

### 4. Modified Files List
**Format**: `filename, PASS or FAILED, lines added/deleted/modified, modification description`
- List all modified files with their review status
- Include line count changes
- Provide brief description of modifications

### 5. Functional Enhancement Description
- Provide detailed description of functional improvements after changes
- Explain the benefits and value added by the modifications

### 6. Further Improvement Suggestions
- Describe suggestions for additional improvements needed
- Identify areas that require further enhancement or optimization