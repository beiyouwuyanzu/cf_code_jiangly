// url:https://codeforces.com/contest/1533/problem/D
// time:2021-07-02 21:13:36
// name:D-StringSearching

import kotlin.collections.*

fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readInts() = readLn().split(' ').map(String::toInt)
fun readLong() = readLn().toInt()
fun readLongs() = readLn().split(' ').map(String::toLong)

fun main() {
    var (n, m) = readInts()
    var cnt = HashMap<String, Int>()
    repeat(n) {
        var s = readLn()
        if (cnt.containsKey(s)) {
            cnt.replace(s, cnt.get(s)!! + 1)
        } else {
            cnt.put(s, 1)
        }
    }
    var q = readInt()
    repeat(q) {
        var t = readLn()
        var sub = HashSet<String>()
        for (i in 0..m) {
            sub.add("${t.slice(0 until i)}${t.slice(i + 1..m)}")
        }
        var ans = 0
        for (s in sub) {
            if (cnt.containsKey(s)) {
                ans += cnt.get(s)!!
            }
        }
        println(ans)
    }
}
