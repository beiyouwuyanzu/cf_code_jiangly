// url:https://codeforces.com/contest/1533/problem/F
// time:2021-07-02 21:41:53
// name:F-BinaryStringPartition

import kotlin.collections.*

fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readInts() = readLn().split(' ').map(String::toInt)
fun readLong() = readLn().toInt()
fun readLongs() = readLn().split(' ').map(String::toLong)

fun main() {
    val s = readLn().toCharArray().map(Char::toString).map(String::toInt)
    val n = s.size
    val cnt = Array(2, {IntArray(n + 1)})
    val pos = Array(2, {ArrayList<Int>()})
    for (c in 0..1) {
        for (i in 0 until n) {
            cnt[c][i + 1] = cnt[c][i] + if (s[i] == c) 1 else 0
            if (s[i] == c) {
                pos[c].add(i)
            }
        }
        while (pos[c].size < 2 * n + 1) {
            pos[c].add(n)
        }
    }
    for (k in 1..n) {
        var cur = 0
        var ans = 0
        while (cur < n) {
            ans++
            cur = maxOf(pos[0][cnt[0][cur] + k], pos[1][cnt[1][cur] + k])
        }
        print(ans)
        if (k < n) {
            print(" ")
        }
    }
    println("")
}
