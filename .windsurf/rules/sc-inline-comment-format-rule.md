---
trigger: always_on
---

# Rule: sc-inline-comment-format-rule

Inline comment format specification

## Inline Comment Format Structure

### 1. Format
**Format**: 
[Inline Comment]
- priority
- standard: cweTop25 / owaspTop10 / sercomm / reserved
- issue name
- description
- suggestion

### 2. Note
- suggestion: should display the detail of issue fix
- **low priority inline comment can be omitted**

### 3. Rules & Standards Map
the mapping of standard and rule files:
|standard|rule file|
|---|---|
|cweTop25|sc-code-check-cwe-top25-rule.md|
|owapsTop10|sc-code-check-owaps-top10-rule.md|
|sercomm|sc-code-check-sercomm-rule.md|
|reserved|sc-code-check-reserved-rule.md|