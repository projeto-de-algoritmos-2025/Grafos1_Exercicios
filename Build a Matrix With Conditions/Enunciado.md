# [Build a Matrix With Conditions](https://leetcode.com/problems/build-a-matrix-with-conditions/description/?envType=problem-list-v2&envId=topological-sort)

You are given a positive integer `k`. You are also given:
- A 2D integer array `rowConditions` of size `n` where `rowConditions[i] = [abovei, belowi]`, and
- A 2D integer array `colConditions` of size `m` where `colConditions[i] = [lefti, righti]`.

The two arrays contain integers from `1` to `k`.

## Problem Statement

You have to build a `k x k` matrix that contains each of the numbers from `1` to `k` exactly once. The remaining cells should have the value `0`.

The matrix must satisfy the following conditions:
1. For each `[abovei, belowi]` in `rowConditions`, the number `abovei` must appear in a row that is strictly above the row containing `belowi`.
2. For each `[lefti, righti]` in `colConditions`, the number `lefti` must appear in a column that is strictly left of the column containing `righti`.

Return any valid matrix that satisfies all conditions. If no such matrix exists, return an empty matrix.

## Examples

### Example 1

**Input:**

k = 3
rowConditions = [[1,2],[3,2]]
colConditions = [[2,1],[3,2]]



**Output:**

[[3,0,0],[0,0,1],[0,2,0]]



**Explanation:**
- Row conditions:
  - 1 is above 2 (row 1 above row 2)
  - 3 is above 2 (row 0 above row 2)
- Column conditions:
  - 2 is left of 1 (column 1 left of column 2)
  - 3 is left of 2 (column 0 left of column 1)

### Example 2

**Input:**

k = 3
rowConditions = [[1,2],[2,3],[3,1],[2,3]]
colConditions = [[2,1]]


**Output:**

**Explanation:** The conditions create a contradiction (3 must be both below and above 1), making it impossible to construct a valid matrix.

## Constraints

- `2 <= k <= 400`
- `1 <= rowConditions.length, colConditions.length <= 10⁴`
- `rowConditions[i].length == colConditions[i].length == 2`
- `1 <= abovei, belowi, lefti, righti <= k`
- `abovei != belowi`
- `lefti != righti`

## Solution Approach

This problem can be solved using topological sorting:
1. **Row Constraints**: Create a directed graph from row conditions and perform topological sort to determine row positions
2. **Column Constraints**: Create another directed graph from column conditions and perform topological sort to determine column positions
3. **Validation**: Check for cycles in either graph (which would make the problem unsolvable)
4. **Matrix Construction**: Place each number at the intersection of its determined row and column positions

Note: The solution requires handling potentially large constraints efficiently (k up to 400 and up to 10⁴ conditions).