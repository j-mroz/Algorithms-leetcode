func longestConsecutive(nums []int) int {
    numMap := make(map[int]int)

    for _, value := range nums {
        numMap[value] = 1
    }

    longest := 0
    for start, _ := range numMap {
        if _, inMap := numMap[start-1]; inMap {
            continue
        }

        end := start + 1
        for _, inMap := numMap[end]; inMap; {
            end++
            _, inMap = numMap[end]
        }
        // end is 1 away from last
        if (end - start > longest) {
            longest = end - start
        }
    }

    return longest
}
