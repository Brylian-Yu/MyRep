---
trigger: always_on
---

# Rule: sc-local-review-rule

- Local code review rules for diffed files based on memory analysis

## Review Principles

1. **Diff-based Review**: Based on memory `memory_diff_local`, find diffed files and perform code review on these changed files only.

## Review Content

### 1. Functional Analysis
- **Objective**: Based on all source code, perform functional analysis of the diffed code sections
- **Requirements**: 
  - Determine if changes provide beneficial effects
  - Provide specific descriptions of the benefits or improvements

### 2. Problem Analysis

#### 2.1 Critical Errors and Potential Risks
Check for the existence of:

**Memory-related Issues:**
- Memory leaks
- Wild pointers
- Memory boundary violations
- Memory alignment problems

**Pointer-related Issues:**
- Null pointer references
- Dangling pointers
- Pointer type conversion issues

**Data Type Issues:**
- Implicit type conversion problems
- Data overflow
- Uninitialized variables

**Concurrency and Multi-threading Issues:**
- Race conditions
- Deadlocks
- Thread safety problems

**Compilation and Linking Issues:**
- Undefined references
- Duplicate definitions
- Header file protection issues

**Standard Library and Third-party Library Issues:**
- Incorrect usage of standard library functions

#### 2.2 Obvious Deficiencies
Identify and describe specific issues with necessary modification suggestions:

**Performance Issues:**
- Algorithm efficiency problems
- Frequent memory allocation and deallocation
- Frequent I/O operations

**Functional Defects:**
- Interactivity issues
- Completeness problems
- Extensibility limitations

#### 2.3 Detailed Modification Suggestions
- **High Priority**: Critical errors or potential risks
- **Low Priority**: Obvious deficiencies

## Review Results

### Pass/Fail List for All Diffed Files

**Criteria:**
- **PASS**: Modifications have no issues AND no critical errors or potential risks
- **FAILED**: Any critical errors, potential risks, or significant issues found

**Output Format:**
List all diffed files with their review status (PASS/FAILED) and specific reasons for failures.