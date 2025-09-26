---
trigger: always_on
---

# Rule: sc-inline-comment-reply-format-rule

Inline comment reply format specification

## Inline Comment Reply Format Structure

### 1. Format
**Format**: [desp_feedback][sugt_feedback]
- desp_feedback: the usefulness feedback of the description in inine comment format
- sugt_feedback: the usefulness feedback of the suggestion in inine comment format

**reference**:
- inline comment format: see **sc-inline-comment-format-rule**

### 2. Feedback Understand
- 2.1 extract the desp_feedback and sugt_feedback from the reply format
- 2.2 extract the description and suggestion from the inline comment format
- 3.3 understand the meaning of the feedback to conclude the usefulness level of description and suggestion

**usefulness level**
- Useful: no need to improve code check rules
- Not Useful: need to improve code check rules