// url:https://codeforces.com/contest/1532/problem/F
// time:2021-06-30 13:09:47
// name:F-PrefixesandSuffixes

import kotlin.collections.*

fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readInts() = readLn().split(' ').map(String::toInt)
fun readLong() = readLn().toInt()
fun readLongs() = readLn().split(' ').map(String::toLong)

fun main() {
    var n = readInt()
    var s = Array<String>(2 * n - 2, {""})
    var count = IntArray(26)
    var a = ""
    var b = ""
    for (i in 0 until 2 * n - 2) {
        s[i] = readLn()
        count[s[i][0].toInt() - 'a'.toInt()]++
        if (s[i].length == n - 1) {
            if (a == "") {
                a = s[i]
            } else {
                b = s[i]
            }
        }
    }
    var ab = a.slice(1 until n - 1) == b.slice(0 until n - 2)
    var ba = b.slice(1 until n - 1) == a.slice(0 until n - 2)
    var t = ""
    if (ab && (!ba || count[a[0].toInt() - 'a'.toInt()] >= n - 1)) {
        t = "${a[0]}$b"
    } else {
        t = "${b[0]}$a"
    }
    var ans = CharArray(2 * n - 2)
    var usedP = BooleanArray(n)
    for (i in 0 until 2 * n - 2) {
        if (s[i] == t.slice(0 until s[i].length) && !usedP[s[i].length]) {
            ans[i] = 'P'
            usedP[s[i].length] = true
        } else {
            ans[i] = 'S'
        }
    }
    println(ans.joinToString(""))
}
