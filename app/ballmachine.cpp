#include <bits/ranges_algo.h>
#include <exception>
#include <gtest/gtest.h>
#include <iterator>
#include <memory>
#include <algorithm>
#include <map>
#include <ostream>
#include <ranges>
#include <stdexcept>
#include <math.h>

/*
 * 2nd Round with Hunter: Coding Question / Task : 
 * Given N buckets And M balls where M=N-1 You 
 * have balls distributed across buckets. There 
 * is a robot arm which can move ball from slot A to B. 
 * There is always an existing array P[i] containing 
 * position of ball i in the buckets Build an 
 * algorithm to sort balls in all buckets. 
 * So that last entry was empty
 **/

struct Ball
{
    int number;
    explicit Ball(int number_)
    :   number(number_)
    {
    }
    Ball(){}
};

using Bucket = std::vector<Ball>;
using BucketPtr = Bucket*;

class RobotArm
{
private:
    size_t _numBuckets;
    size_t _numBalls;
    std::vector<BucketPtr> _ballPositions;
public:
    RobotArm(std::vector<Bucket>& buckets_)
    :   _numBuckets(buckets_.size())
    ,   _numBalls(0)
    ,   _ballPositions()
    {
        for (auto& bucket : buckets_)
        {
            for (auto it = bucket.begin(); it != bucket.end(); it++)
            {
                _numBalls++;
            }
            _ballPositions.reserve(_numBalls);
            for (auto& ball : bucket)
                _ballPositions[ball.number] = &bucket;
        }
    }

    void sortBalls(std::vector<Bucket>& buckets_)
    {
        // get the bucket we will store balls in
        auto& lastBucket = buckets_[buckets_.size() - 1];
        // populate it
        for (size_t i(0); i < buckets_.size()-1; i++)
        {
            for (auto& ball : buckets_[i])
                moveBall(ball.number, buckets_[i], lastBucket);
        }
        // sort it
        std::sort(lastBucket.begin(), lastBucket.end(), [](const Ball& a, const Ball& b) { return a.number > b.number; });
        // inner loop range
        size_t ballsPerBucket = std::ceil(_numBalls/(_numBuckets-1)); // check non-zero
        // stopping condition
        size_t ballsMoved = 0;
        for (size_t i(0); i < (_numBuckets - 1); i++)
        {
            auto& targetBucket = buckets_[i];
            for(size_t j(0); j < ballsPerBucket; j++)
            {
                int ballToMove = lastBucket[0].number;
                moveBall(ballToMove, lastBucket, targetBucket);
                if (ballsMoved == _numBalls)
                    return;
            }
        }
    }

    void moveBall(int ballNum, Bucket& fromBucket_, Bucket& toBucket_)
    {
        // get reference
        for (auto it = fromBucket_.begin(); it != fromBucket_.end(); it++)
        {
            if (it->number == ballNum)
            {
                toBucket_.push_back(std::move(*it));
                fromBucket_.erase(it);
                return;
            }
        }
        throw std::out_of_range("Ball " + std::to_string(ballNum) + " not in vector");
    }
};


int canitwork(int v)
{
    int result(0);
    for (;;result++)
    {
        if (v < 10) return result;
        if (v < 100) return result + 1;
        if (v < 1000) return result + 2;
        if (v < 10000) return result + 3;
        if (v < 100000) return result + 4;
        if (v < 10000000) return result + 5;
    }
}
TEST(strstr, canitwork)
{

    int result = 1;
    int v = 0;



}



std::ostream& operator<<(std::ostream& os_, const Ball& ball_)
{
    os_ << "Ball(" << ball_.number << "), ";
    return os_;
}

std::ostream& operator << (std::ostream& os_, const Bucket& bucket_)
{
    for (const auto& ball : bucket_)
        os_ << ball;
    os_ << '\n';
    return os_;
}

TEST(RobotArm, smoke_test)
{
    // N Balls, N-1 Buckets
    std::vector<Bucket> buckets = {
        {Ball(4)},
        {Ball(1), Ball(3)},
        {Ball(5), Ball(6)},
        {Ball(8), Ball(7)},
        {Ball(10), Ball(9)},
        {Ball(2), Ball(11)}
    };
    for (auto& bucket : buckets)
        bucket.reserve(10);
    // {Ball(1), Ball(2)}
    // {Ball(3), Ball(4)},
    // {}


    auto robotPtr = std::make_shared<RobotArm>(buckets);
    robotPtr->sortBalls(buckets);
    for (auto& bucket : buckets)
    {
        if (buckets.size() != 0)
            std::cout << bucket; //<< '\n';
    }

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

