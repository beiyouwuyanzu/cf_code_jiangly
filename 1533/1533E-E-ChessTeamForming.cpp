// url:https://codeforces.com/contest/1533/problem/E
// time:2021-07-02 21:30:33
// name:E-ChessTeamForming

import kotlin.collections.*

fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readInts() = readLn().split(' ').map(String::toInt)
fun readLong() = readLn().toInt()
fun readLongs() = readLn().split(' ').map(String::toLong)

fun main() {
    val n = readInt()
    val a = readInts().sorted()
    val b = readInts().sorted()
    val m = readInt()
    val c = readInts()
    val ans = IntArray(m)
    val pre = IntArray(n + 1, {Int.MIN_VALUE})
    val suf = IntArray(n + 1, {Int.MIN_VALUE})
    for (i in 0 until n) {
        pre[i + 1] = maxOf(pre[i], b[i] - a[i])
    }
    for (i in n - 1 downTo 0) {
        suf[i] = maxOf(suf[i + 1], b[i + 1] - a[i])
    }
    for (i in 0 until m) {
        var p = a.binarySearch(c[i])
        if (p < 0) {
            p = -p - 1
        }
        ans[i] = maxOf(pre[p], suf[p], b[p] - c[i])
    }
    println(ans.map(Int::toString).joinToString(" "))
}
