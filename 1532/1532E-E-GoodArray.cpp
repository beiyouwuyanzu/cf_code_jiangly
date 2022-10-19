// url:https://codeforces.com/contest/1532/problem/E
// time:2021-06-30 12:42:17
// name:E-GoodArray

import kotlin.collections.*

fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readInts() = readLn().split(' ').map(String::toInt)
fun readLong() = readLn().toInt()
fun readLongs() = readLn().split(' ').map(String::toLong)

fun main() {
    var n = readInt()
    var a = readLongs()
    var ans = ArrayList<Int>()
    var sm = a.sum()
    var mx = arrayOf(0L, 0L)
    for (x in a) {
        var y = x
        for (j in 0..1) {
            if (x > mx[j]) {
                var t = y
                y = mx[j]
                mx[j] = t
            }
        }
    }
    for (i in 0 until n) {
        if (a[i] < mx[0] && sm - a[i] == 2 * mx[0]) {
            ans.add(i + 1)
        }
        if (a[i] == mx[0] && sm - mx[0] == 2 * mx[1]) {
            ans.add(i + 1)
        }
    }
    println(ans.size)
    println(ans.map(Int::toString).joinToString(" "))
}
