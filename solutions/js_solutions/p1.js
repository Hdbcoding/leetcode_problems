/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function(nums, target) {
    let map = {};
    for (let i = 0; i < nums.length; i++){
        let x = target - nums[i];
        if (map[x] !== undefined) return [map[x], i];
        map[nums[i]] = i;
    }
};