# 局部模板匹配
最常见的图像块是边数为奇数的正方形，关键点的位置就是正方形的中心。可通过比较块内像素的强度值来衡量两个正方形图像块的相似度。常见的方案是采用简单的**差的平方和(Sum of Squared Differences,SSD)**算法。
## C++学习
···
std::nth_element
template <class RandomAccessIterator>
  void nth_element (RandomAccessIterator first, RandomAccessIterator nth,
                    RandomAccessIterator last);
custom (2)
template <class RandomAccessIterator, class Compare>
  void nth_element (RandomAccessIterator first, RandomAccessIterator nth,
                    RandomAccessIterator last, Compare comp);

Sort element in range
Rearranges the elements in the range [first,last), in such a way that the element at the nth position is the element that would be in that position in a sorted sequence.

The other elements are left without any specific order, except that none of the elements preceding nth are greater than it, and none of the elements following it are less.

The elements are compared using operator< for the first version, and comp for the second.
···
