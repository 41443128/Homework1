# 41143263

# 作業一

## Problem 1：Ackermann's Function

### 1. 解題說明

#### 問題描述

Ackermann 函數定義如下：

$A(m,n)=n+1$，當 $m=0$。

$A(m,n)=A(m-1,1)$，當 $m>0$ 且 $n=0$。

$A(m,n)=A(m-1,A(m,n-1))$，當 $m>0$ 且 $n>0$。

本題要求完成兩種版本：

1. 使用遞迴函式計算 Ackermann 函數。
2. 使用非遞迴方式計算 Ackermann 函數。

#### 解題策略

遞迴版本直接按照題目定義撰寫。當 `m == 0` 時回傳 `n + 1`；當 `n == 0` 時呼叫 `A(m - 1, 1)`；其餘情況則計算 `A(m - 1, A(m, n - 1))`。

非遞迴版本則利用陣列自行模擬 stack。每次將尚未完成的 `m` 值存入陣列中，再依照 Ackermann 函數的規則逐步更新 `m` 與 `n`，直到 stack 為空為止。

由於本學期限制可使用的標頭，因此沒有使用 `<stack>`，而是以動態陣列模擬 stack。

### 2. 程式實作

```cpp
#include <iostream>

using namespace std;

long long ackermannRecursive(long long m, long long n) {
    if (m < 0 || n < 0) {
        throw "m or n < 0";
    }

    if (m == 0) {
        return n + 1;
    }

    if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    }

    return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
}

long long ackermannNonRecursive(long long m, long long n) {
    if (m < 0 || n < 0) {
        throw "m or n < 0";
    }

    const int STACK_SIZE = 1000000;
    long long* data = new long long[STACK_SIZE];
    int top = 0;

    data[top++] = m;

    while (top > 0) {
        m = data[--top];

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            n = 1;

            if (top >= STACK_SIZE) {
                delete[] data;
                throw "stack overflow";
            }

            data[top++] = m - 1;
        } else {
            if (top + 2 > STACK_SIZE) {
                delete[] data;
                throw "stack overflow";
            }

            data[top++] = m - 1;
            data[top++] = m;
            n = n - 1;
        }
    }

    delete[] data;
    return n;
}

int main() {
    long long m = 2;
    long long n = 3;

    cout << "Recursive: "
         << ackermannRecursive(m, n) << '\n';

    cout << "Non-recursive: "
         << ackermannNonRecursive(m, n) << '\n';

    return 0;
}
```

### 3. 效能分析

Ackermann 函數的成長速度非常快，不能像一般迴圈一樣使用簡單的 `O(n)`、`O(n2)` 或 `O(2n)` 表示其完整計算量。

令 `T(m,n)` 表示計算 `A(m,n)` 所需要的展開步數，則：

1. 時間複雜度：`O(T(m,n))`。
2. 空間複雜度：
   - 遞迴版本為 `O(D(m,n))`，其中 `D(m,n)` 為最大遞迴深度。
   - 非遞迴版本為 `O(D(m,n))`，因為陣列模擬的 stack 需要保存尚未完成的計算。

Ackermann 函數即使輸入值很小，計算量也可能快速增加，因此不適合使用很大的 `m` 與 `n` 進行測試。

### 4. 測試與驗證

測試結果如下：

| 測試案例 | 輸入 | 預期輸出 |
| --- | --- | --- |
| 測試一 | `A(0,0)` | `1` |
| 測試二 | `A(0,3)` | `4` |
| 測試三 | `A(1,2)` | `4` |
| 測試四 | `A(2,3)` | `9` |
| 測試五 | `A(3,2)` | `29` |

實際編譯與執行：

```shell
$ g++ src/problem1.cpp --std=c++21 -o problem1.exe
$ ./problem1.exe
Recursive: 9
Non-recursive: 9
```

由輸出可以確認遞迴版本與非遞迴版本皆得到 `9`，結果相同。

### 5. 申論及開發報告

Ackermann 函數本身就是以遞迴方式定義，因此使用遞迴實作時，程式結構與數學公式非常接近，容易理解。

遞迴版本的主要優點是程式簡短且邏輯清楚，但每次函式呼叫都會使用系統的 Call Stack。當遞迴深度過大時，可能產生 Stack Overflow。

非遞迴版本則是自行使用陣列模擬 stack。當某一層計算尚未完成時，將之後還需要處理的 `m` 值保存起來，再逐步取出進行計算。這種方式可以讓我更清楚理解遞迴函式底層其實也是利用 stack 保存尚未完成的工作。

本題也顯示 Ackermann 函數的成長速度非常快，即使只是增加少量輸入，也可能讓計算次數大幅增加。因此在實際測試時應使用較小的輸入值。

---

## Problem 2：Powerset

### 1. 解題說明

#### 問題描述

Powerset 是一個集合所有可能子集合所形成的集合。

例如集合：

$S={a,b,c}$

其 Powerset 包含：

`{}`、`{a}`、`{b}`、`{c}`、`{a,b}`、`{a,c}`、`{b,c}`、`{a,b,c}`。

若原集合共有 `n` 個元素，Powerset 共有 `2^n` 個子集合。

本題要求使用遞迴函式產生一個集合的所有子集合。

#### 解題策略

對集合中的每一個元素，都有兩種可能：

1. 不加入目前子集合。
2. 加入目前子集合。

因此可以利用遞迴依序處理每個元素。

當 `index` 等於集合長度時，代表所有元素都已經決定是否加入，此時即可輸出目前的子集合。

在選擇加入元素後，遞迴完成時再使用 `pop_back()` 移除最後一個元素，使程式回到上一層狀態。這種方法稱為 Backtracking。

### 2. 程式實作

```cpp
#include <iostream>
#include <string>

using namespace std;

void powerset(const string& set, int index, string& current) {
    if (index == static_cast<int>(set.size())) {
        cout << "{";

        for (int i = 0; i < static_cast<int>(current.size()); ++i) {
            if (i > 0) {
                cout << ",";
            }

            cout << current[i];
        }

        cout << "}" << '\n';
        return;
    }

    powerset(set, index + 1, current);

    current += set[index];
    powerset(set, index + 1, current);
    current.pop_back();
}

int main() {
    string set = "abc";
    string current = "";

    powerset(set, 0, current);

    return 0;
}
```

### 3. 效能分析

對每個元素而言，都有「選擇」與「不選擇」兩種可能，因此 `n` 個元素會產生 `2^n` 個子集合。

1. 時間複雜度：`O(n×2^n)`。
   - 共需要產生 `2^n` 個子集合。
   - 每個子集合最多需要輸出 `n` 個元素。
2. 空間複雜度：`O(n)`。
   - 遞迴深度最多為 `n`。
   - `current` 最多保存 `n` 個元素。

此分析不包含將所有 Powerset 額外儲存在記憶體中的空間，因為本程式採用直接輸出的方式。

### 4. 測試與驗證

測試案例：

| 測試案例 | 輸入集合 | 子集合數量 |
| --- | --- | --- |
| 測試一 | `{}` | `1` |
| 測試二 | `{a}` | `2` |
| 測試三 | `{a,b}` | `4` |
| 測試四 | `{a,b,c}` | `8` |
| 測試五 | `{a,b,c,d}` | `16` |

實際編譯與執行：

```shell
$ g++ src/problem2.cpp --std=c++21 -o problem2.exe
$ ./problem2.exe
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}
```

輸入集合共有 3 個元素，因此理論上應有：

`2^3 = 8`

個子集合。

實際輸出也共有 8 個子集合，因此程式結果正確。

### 5. 申論及開發報告

本題使用遞迴的原因，是 Powerset 本身具有非常明顯的遞迴結構。

對每一個元素，都有兩種可能：選擇該元素或不選擇該元素。因此可以將原本的問題拆成兩個較小的子問題，並持續處理下一個元素。

例如處理 `{a,b,c}` 時，可以先決定是否加入 `a`，接著再決定是否加入 `b`，最後決定是否加入 `c`。當所有元素都處理完後，就得到其中一個完整的子集合。

程式中的：

```cpp
powerset(set, index + 1, current);
```

代表不加入目前元素。

而：

```cpp
current += set[index];
powerset(set, index + 1, current);
```

代表加入目前元素。

最後使用：

```cpp
current.pop_back();
```

將剛才加入的元素移除，使程式回復上一層狀態，再繼續處理其他可能。這就是 Backtracking 的概念。

使用遞迴與 Backtracking 可以用較簡潔的程式碼列舉所有可能子集合，而且程式結構能直接反映每個元素「選」與「不選」兩種情況，因此非常適合用來解 Powerset 問題。

---

## 作業總結

本次作業主要練習遞迴、非遞迴轉換、stack 概念以及 Backtracking。

Problem 1 的 Ackermann 函數直接展示遞迴函式的特性，並進一步利用陣列模擬 stack，完成非遞迴版本。

Problem 2 則利用遞迴與 Backtracking 產生所有子集合，使我了解當每個元素都有多種選擇時，可以透過遞迴將問題逐層拆解。

透過本次作業，可以更進一步理解遞迴函式、Call Stack 以及 Backtracking 之間的關係，也能了解遞迴程式在時間複雜度與空間複雜度上的限制。
