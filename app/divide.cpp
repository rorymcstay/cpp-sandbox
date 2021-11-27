#include <algorithm>
#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

#include <stdio.h>
#include <vector>


class Solutions {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> mergedArray;
        // loop over the smallest index
            // increment
        auto num1_it = nums1.begin();
        auto num2_it = nums2.begin();

        for (;num1_it != nums1.end() && num2_it != nums2.end();)
        {
            int to_insert = *(*num1_it < *num2_it ? num1_it++ : num2_it++);
            mergedArray.push_back(to_insert);
        }
        auto remainder = num1_it == nums1.end() ? std::pair(num2_it, nums2.end()) : std::pair(num1_it, nums1.end());
        while (remainder.first != remainder.second)
        {
            mergedArray.push_back(*remainder.first++);
        }
        int size = mergedArray.size();
        if (size % 2 == 0)
            return (mergedArray[size/2 - 1] + mergedArray[size/2 + 1])/2.0;
        else
            return mergedArray[(size-1)/2];
    }
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        // * * * * * *
        // * * * * . *
        // * . . . . *
        // * . . . . * 
        // * * * * * *
        //
        auto top_most_edge = std::pair(matrix.begin()->begin(),matrix.begin()->end());

    }
};

TEST(Solutions, findMedianSortedArrays)
{
    auto solution = new Solutions();
    std::vector<int> nums1 = {1,2};
    std::vector<int> nums2 = {3,4};
    int expected = 2.5;
    int answer = solution->findMedianSortedArrays(nums1, nums2);
    ASSERT_TRUE(expected == answer);
}

TEST(Solutions, findMedianSortedArrays_1)
{
    auto solution = new Solutions();
    std::vector<int> nums1 = {1,3,5,7,9,11,13};
    std::vector<int> nums2 = {2,4,6,8,10,12};
    // 1,2,3,4,5,6,7,8,9,10,11,12,13
    double expected = 7;
    int answer = solution->findMedianSortedArrays(nums1, nums2);
    std::cout << "expected=" << expected << " actual=" << answer << '\n';
    ASSERT_TRUE(expected == answer);
}


float divide(int numerator, int denominator, int count=0, int places=1, int significant_figures=2)
{
    int diff = numerator;
    //      1 >=   10
    while (diff >= denominator)
    {
        diff = diff - denominator;
        if (diff >= 0) ++count;
        divide(diff, denominator, count);
    }
    if (diff - denominator < 0)
    {
        int res = divide(denominator, std::abs(diff));
        switch (res)
        {
            case 1:
                return count - float(1/10^(places));
            case 2:
                return count - float(2/10^(places));
            case 3:
                return count - float(3/10^(places));
            case 4:
                return count - float(4/10^(places));
            case 5:
                return count - float(5/10^(places));
            case 6:
                return count - float(6/10^(places));
            case 7:
                return count - float(7/10^(places));
            case 8:
                return count - float(8/10^(places));
            case 9:
                return count - float(9/10^(places));
            case 10:
                return count - 1;
            default:
                throw std::out_of_range("correction not handled");
        }
    }
    else if (diff - denominator == 0)
    {
        return count;
    }
    else if (diff - denominator > 0)
    {
        int res = divide( denominator, diff);
        switch(res)
        {
            case 0:
                return count;
            case 1:
                return count + float(1/10^(places));
            case 2:
                return count + float(2/10^(places));
            case 3:
                return count + float(3/10^(places));
            case 4:
                return count + float(4/10^(places));
            case 5:
                return count + float(5/10^(places));
            case 6:
                return count + float(6/10^(places)); 
            case 7:
                return count + float(7/10^(places));
            case 8:
                return count + float(8/10^(places));
            case 9:
                return count + float(9/10^(places));
            case 10:
                return count + 1;
            default:
                throw std::out_of_range("correction not handled");
        }
    }
}


TEST(divide, smoke)
{

    std::cout << "divide(10,1)=" <<  divide(10, 1) << '\n';
    std::cout << "divide(1,10)=" <<  divide(1,10) << '\n';
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
    
long isValidBSTHelper(TreeNode* root, long min_left, long max_right, bool went_left, bool went_right)
{
    /*
     *
            5
          /   \
         4     6
        / \   / \
       .   . 3   7

     */
    
    bool valid = true;

    if (root->left)
        min_left = root->left->val < min_left ? root->val : min_left;
    if (root->right)
        max_right = root->right->val > max_right ? root->val : max_right;
    if (root->left) {
        if (!(root->left->val < root->val))
            return false;
        std::cout << "Return true " << root->val << " min_left=" << min_left << " max_right=" << max_right << '\n';
        if (!isValidBSTHelper(root->left, min_left, max_right, true, false))
        {
            return false;
        }
    } else if (went_left) {
        valid = root->val < min_left;
    } else if (went_right) {
        valid = root->val > max_right;
    }
    if (root->right) {
        if (!(root->right->val > root->val))
            return false;
        std::cout << "Return true " << root->val << " min_left=" << min_left << " max_right=" << max_right << '\n';
        if (!isValidBSTHelper(root->right, min_left, max_right, false, true))
            return false;
    }
    std::cout << "Return true " << root->val << '\n';
    return valid;
}
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        /**
         * right child > root && left child < root
         **/
        long min_left = root->val;
        long max_right = root->val;
        return isValidBSTHelper(root, min_left, max_right);

    }
};

TreeNode* make_tree(std::vector<int> values, int i=0, TreeNode* root=nullptr)
{
    if (values.size() % 3 != 0)
        throw std::out_of_range("List must be multiple of three");
    if (not root)
        root = new TreeNode();
    if (values[i] != NULL)
        root->val = values[i];
    if (values[i+1] != NULL)
        root->left = new TreeNode(values[i]);
    if (values[i+2] != NULL)
        root->right = new TreeNode(values[i]);
    if (index+1 == values.size())
        return root;
    else
        return make_tree(values, i+3, root);
}

TEST(isValidBST, smoke)
{
    std::vector<int> params = {1,2,3};
    make_tree(params);

    std::vector<int> params2 = {1, 2, NULL};
    make_tree(params2);
    
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

