---
description: Statistics of reviewer activities and comment usefulness
auto_execution_mode: 1
---

# Review Statistics and Comment Analysis

This workflow helps you analyze windsurf review activities and comment reply feedback usefulness across all projects with improved data validation and error prevention.

## Prerequisites

- Gitlab MCP server configured
- Appropriate permissions to access the projects
- Access to merge requests and review data

## Usage

1. Run this workflow to generate comprehensive review statistics
2. The output will include:
- total number of MRs per project
- number of windsurf reviewed MRs per project
- total number of inline comment reply feedback per project(include description feedback and suggestion feedback)
- number of high priority inline comment reply feedback per project(include description feedback and suggestion feedback)
- number of medium prority inline comment reply feedback per project(include description feedback and suggestion feedback)
- number of low prority inline comment reply feedback per project(include description feedback and suggestion feedback)
- total number of useful inline comment reply feedback per project(include description feedback and suggestion feedback)
- total number of not useful inline comment reply feedback per project(include description feedback and suggestion feedback)
- number of useful high priority inline comment reply feedback per project(description feedback only)
- number of useful high priority inline comment reply feedback per project(suggestion feedback only)
- number of not useful high priority inline comment reply feedback per project(description feedback only)
- number of not useful high priority inline comment reply feedback per project(suggestion feedback only)
- number of useful medium priority inline comment reply feedback per project(description feedback only)
- number of useful medium priority inline comment reply feedback per project(suggestion feedback only)
- number of not useful medium priority inline comment reply feedback per project(description feedback only)
- number of not useful medium priority inline comment reply feedback per project(suggestion feedback only)
- number of useful low priority inline comment reply feedback per project(description feedback only)
- number of useful low priority inline comment reply feedback per project(suggestion feedback only)
- number of not useful low priority inline comment reply feedback per project(description feedback only)
- number of not useful low priority inline comment reply feedback per project(suggestion feedback only)


## Steps

### Step 1: Get all projects with validation
First, we need to list all projects to analyze across the organization.

### Step 2: Collect MR data for each project with strict verification
For each project, we'll collect:
- **ALL MRs systematically** - not just a sample, and **list them in a table format**
- **Windsurf reviewed** MRs should include **"[Windsurf Review]"** in **overall comments (using notes API)**
- All **inline comments (using discussion API)** for each **windsurf reviewed** MR

### Step 3: Analyze Inline comment usefulness with data validation
The format of the inline comment reply for categorization referencing to:
- **sc-inline-comment-reply-format-rule**

In **windsurf reviewed** MR, categorize all inline comments reply feedback by analyzing the reply format:
- **Useful**: Comments that provide useful description or useful suggestion.
- **Not Useful**: Comments that provide not useful description or not useful suggestion.
- **Uncategorized**: Comments without proper reply format

### Step 4: Generate statistics report with accuracy verification

## Output Format

### Statistics MRs Level per project
| Project | Total MRs | Windsurf Reviewed MRs| 
|----|----|-----|
| PN1 | 100 | 80 (80%) |
| PN2 | 200 | 60 (30%) |

### Statistics Inline Comments reply **description feedback** Level per project
| Priority | Total | Useful | Not Useful | Uncategorized |
|----|----|-----|----|-----|
| High | 200 | 100 (50%) | 20 (10%)| 80 (40%)|
| Medium | 200 | 100 (50%) | 20 (10%)| 80 (40%)|
| Low | 200 | 100 (50%) | 20 (10%)| 80 (40%)|

### Statistics Inline Comments reply **suggestion feedback** Level per project
| Priority | Total | Useful | Not Useful | Uncategorized |
|----|----|-----|----|-----|
| High | 200 | 100 (50%) | 20 (10%)| 80 (40%)|
| Medium | 200 | 100 (50%) | 20 (10%)| 80 (40%)|
| Low | 200 | 100 (50%) | 20 (10%)| 80 (40%)|

## Implementation Details

The workflow will:

1. **Fetch Projects**: Use APIs get all accessible projects
2. **Fetch MRs**: For each project, use APIs to get all MRs
3. **Filter Windsurf Reviews**: Look for MRs with **overall comments** containing **"[Windsurf Review]"**
4. **Analyze Comments**: Fetch all **inline comments reply feedback** and categorize them
5. **Generate Report**: Compile statistics in the specified table format

## Notes

- Comment usefulness is determined by analyzing **inline comments replay**
- Statistics are generated for the current day by default (or specified time period)
- Time zone is assumed to be CST (China Standard Time)
- All data must be traceable back to specific API responses
- Report includes validation status and data source information

## Automation

This workflow can be scheduled to run daily to track review performance and comment quality trends.

## Troubleshooting

### API Issues:
- Verify your Gitlab MCP server configuration
- Check if you have the necessary permissions to view projects and MRs
- Ensure there are MRs with "[Windsurf Review]" overall comments in the specified time period
- Verify that the Gitlab API endpoints are accessible

## Data Quality Checklist

Before finalizing any report, verify:
- [ ] All MR counts match API response totals
- [ ] No duplicate MR IDs or IIDs in the dataset
- [ ] All timestamps fall within the requested time range
- [ ] All MRs has been check with overall comments (notes API) and inline comments (discussion API)
- [ ] No fabricated or assumed data points
- [ ] All titles and descriptions come directly from API responses
- [ ] Comment analysis is based only on actual comment content
- [ ] Statistical calculations are mathematically correct
- [ ] Report includes data source attribution