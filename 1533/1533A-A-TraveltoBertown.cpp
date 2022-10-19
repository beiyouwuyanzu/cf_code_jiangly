// url:https://codeforces.com/contest/1533/problem/A
// time:2021-07-02 20:33:01
// name:A-TraveltoBertown

import kotlin.collections.*

fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readInts() = readLn().split(' ').map(String::toInt)
fun readLong() = readLn().toInt()
fun readLongs() = readLn().split(' ').map(String::toLong)

fun main() {
    var t = readInt()
    repeat(t) {
        var (n, k) = readInts()
        var ans = 0
        repeat(n) {
            var (l, r) = readInts()
            if (l <= k && k <= r) {
                ans = maxOf(ans, r - k + 1)
            }
        }
        println(ans)
    }
}
