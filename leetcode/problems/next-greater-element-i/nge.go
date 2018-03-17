func nextGreaterElement(nums1 []int, nums2 []int) []int {
    result := make([]int, len(nums1))

    stack := make([]int, 1001)
    ssize := 0

    ngn := make(map[int]int) //next greater number

    for j := len(nums2)-1; j >= 0; j-- {

        for ; ssize > 0 && stack[ssize-1] < nums2[j]; {
            ssize--
        }

        if ssize > 0 {
            ngn[nums2[j]] = stack[ssize-1]
        } else {
            ngn[nums2[j]] = -1
        }

        stack[ssize] = nums2[j]
        ssize++
    }

    for i, value := range nums1 {
        if greater, found := ngn[value]; found {
            result[i] = greater
        } else {
            result[i] = -1
        }
    }

    return result
}
