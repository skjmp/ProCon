# ABC100参加記
問題: https://abc100.contest.atcoder.jp/assignments  
sub: https://beta.atcoder.jp/contests/abc100/submissions?f.User=skjmp

## A
* 隣り合ったケーキは同じ人が取れない

からサイズの半分が、一人が取れる限界な気がします。サイズを見ると16です。境界が怖いのでサンプルで確認すると、素直にサイズの半分が一人で取れる最大のようです。

とりあえずA, B両方共8以下ならOKだろうというような気持ちになりました。
```C++
int main() {
    int a, b;
    cin >> a >> b;
    if (a <= 8 && b <= 8)cout << "Yay!";
    else cout << ":(";
    return 0;
}
```
ただ、A(またはB)が0だった場合も同じ答えになるか怖かったので図を見て確認します。  
大丈夫でした。投げます。通りました。

## B
(今回通ってないです)  
サンプルを見ると各Dで候補の数字は
```
D=0 -> 1,2,3,4,...,99
D=1 -> 100,200,300,...,9900
D=2 -> 10000,20000,30000,...,990000
```
に見えるので、条件を満たすN番目の数字は
```
D=0 -> N*1
D=1 -> N*100 
D=2 -> N*100*100
``` 
に見えます。
コードを生やして 

```C++
int main() {
    ll d, n;
    cin >> d >> n;
    ll k = pow(100, d);
    cout << k*n;
 
    return 0;
}
```
サンプルを確認して出します。WAでした。
「pow関数がdoubleを返すからか？ループにしよう」なんて期待薄な修正をしてWAを重ねます。  
この時点でBに取り組み始めてから15分経っていました。順位表を見ると人々はBを通しているので、問題文のミスというのはなさそうです。

* これ以上粘ってA1完というのはつらい
* 自分のABCの印象としては「Cは高確率で解けて運が良ければDまで解ける」

なのでCに進みます。

## C
数列に操作を繰り返して、何回操作できるでしょうか？問題がでました。
操作は

* a_iを2分の1
* a_iを3倍

で、操作を継続できる条件は

* a_iがすべて整数であること

です。「3倍だけすれば続くな。2分の1は数字が減るから嬉しくないな」なんて考えますが

* 操作はすべてのa_iに行わなければならない
* 操作のうち1つは、2分の1する操作でなければならない

だそうです。

「奇数には2分の1操作は行えない」ことがわかるので、奇数には3倍操作だけが割当たることがわかります。
「奇数に3をかけて偶数に化けたりしないだろうか？」なんてことを考えますが、
(2n-1)(2n-1)=4n^2-4n+1で偶数+1になるのでなさそうです。


次に偶数の取り扱いを考えます。  
偶数が2分の1操作を繰り返されて1(or 他の奇数)になると、その数字はもう2分の1操作に使えなくなるので、1回の数列操作で2分の1操作される数は1個だけにしたいです。  
他の偶数には3倍する操作を割り当てるとして、
「偶数に3倍操作を行った場合に、2分の1できる回数に影響はあるか？」という疑問が湧きました。
2とか4とか6に3をかけて、特に変わらないことを確認します[^1]。

実装に移していきます。

* 「3倍操作によって、数列の操作回数に影響はない」
* 1回の数列操作で2分の1されるのは1要素のみ

ことがわかったので、数列の各要素について、2で割れる回数を計算し、その総和を取ると答えになりそうです。

```C++
int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    rep(i, 0, n)cin >> a[i];
    int cnt = 0;
    rep(i, 0, n) {
        if(a[i] % 2 == 1)continue;
        while (a[i] >= 2){
            a[i] /= 2;
            cnt++;
        }

    }
    cout << cnt << endl;
    return 0;
}
```
サンプルが合いません！
repループの末尾にcerr<<cnt<<endl;を入れて確認します。
84になってましたがよくわかりません。
VisualStudioのデバッグモードで終了時の配列aの中身を確認します。
「奇数だったものはその数字のまま」「他の数字は1」なっています。
「偶数全部が1まで割り切れるっておかしいでしょ」ということでバグに気づきました。直します。

```C++
int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    rep(i, 0, n)cin >> a[i];
    int cnt = 0;
    rep(i, 0, n) {
        while (a[i] >= 2 && a[i] % 2 == 0) {
            a[i] /= 2;
            cnt++;
        }
//        cerr << cnt << endl;

    }
    cout << cnt << endl;
    return 0;
}
```
投げます。通りました。


[^1]: 今にして思えば。2で割って整数になる数は素因数分解したとすると(2^n)*hogeで表されて、2で割る操作はnを-1する操作に他ならないので、ちょっと無駄な実験でしたね。

## D
いい感じに物品を選ぶ問題が出ました。

* ケーキは3属性持っている
* 評価は各属性の評価値の和
* 属性の評価は総和の絶対値で行う

問題見てコードの入力部分書こうと思ったんですが、ケーキを3つのvectorで持つかtupleのvectorで持つか悩んだので書きませんでした。

属性の評価が総和の絶対値で行われるので、例えば属性xyzのうち属性xを良くしようと思ったら

* xが正のものをできるだけ集める
* xが負のものをできるだけ集める

の2パターンが存在することがわかります。

各属性ごとに貪欲に取ろうと考えました。xを最適にしたらy, zが最適にならないケースがありそうでこれは無理そうです。

「もし属性の取りうる値が正だけだったら楽なのになぁ(ケーキごとに3属性の和をとって、その和をソートして上から取ればよいので)」などと考えました。

いまいち方針が浮かばないのでdpを考えました(私にdp力はないです)。とりあえずdpテーブルを「dp[i][j]: i個のケーキからj個選んだ時の最適値」として考えます。  
dpテーブルの遷移がうまく考えられません。
dp[i+1][j]を(取りうるケーキが増えた時を)考えた時、新しいケーキのもつ属性値が既存の最適値を良くするかどうかがわからないので(既存の最適値と符号があってるかわからない)。  
dpテーブルの定義を変えます。
dp[i][j]: i個のケーキからj個選んだ時の、xの総和とyの総和とzの総和」。  
これでも遷移がうまく考えられません。
xyzそれぞれ、正で集めるときと負で集めるときの情報がないと、最適な状態に遷移できない気がします。
そこでdpテーブルに、xyzの正負のパターンを追加することを考えます。数えると8通りで、現実的な数です。

ここで「全部正だったら楽なのに」妄想を思い出します。各属性の正負のパターンを全列挙して、正負のパターンにより各属性値に-1をかけて評価すれば、「全部正だった」場合にうまくいくアルゴリズムが使えて、答えが出る気がしてきました。

「ケーキのどれかの属性でケーキをソートしたい」みたいなことはなさそうなので、ケーキは3つのvectorで持つことに決めて、コーディングしました。


```C++
#define ll long long
#define all(t) t.begin(), t.end()
#define mat(type, row, col, init) vector<vector<type>>(row, vector<type>(col, init));

int bit(int n, int th) {
    return (n >> th) & 1;
}
int main() {
    int n, m;
    cin >> n >> m;
    auto cake = mat(ll, 3, n, 0);
    auto tmpcake = mat(ll, 3, n, 0);
    rep(i, 0, n) {
        // 値取得ループ。初めはcin>>x[i]>>y[i]>>z[i];で取っていたが、
        // bit列で全探索する都合上数値で扱えたほうが良いのでvector<vector<>>で書き換えた
        rep(j, 0, 3)cin >> cake[j][i];
    }

    ll ma = 0;
    rep(com, 0, 8) {
        // このループでどの正負のパターンを探索するかはcomのビットパターンで判別する
        // 例えばcom=0b110なら、属性xでは正を集めて、属性y, zでは負を集めるようなイテレーション
        rep(i, 0, 3) {
            // 各属性について、comのパターンによって-1をかけるやつをやる。
            int sign = (bit(com, i) ? -1 : 1);
            rep(j, 0, n) {
                tmpcake[i][j] = sign*cake[i][j];
            }
        }

        // 補正が終わったので、単純にケーキの3属性の和が大きいものを上から取れば、
        // その正負のパターンでの最適な取り方になるようになった
        vector<ll>sum(n,0);
        rep(j, 0, n) {
            // ケーキごとに属性値の和を取る。
            rep(i, 0, 3) {
                sum[j] += tmpcake[i][j];// サンプルが合わなくて見たら += じゃなくて = になってた
            }
        }
        sort(all(sum));
        ll whole = 0;
        rep(k, 0, m)whole += sum[k]; // 上からM個取るループ
        ma = max(ma, abs(whole)); // サンプルが合わなくて見たらabsしてなかった

    }
    cout << ma << endl;;
    return 0;
}
```

投げます。通りました。やったね！

## B(再チャレンジ)
N=100で変なことになるのはわかったんですが、お恥ずかしながら、「解なしでは？」「そんなわけないやろ」という思考のループに陥りました。
頭の中で

* 「N*100^D」で列挙できる
* N=100で(D+1)回割れてしまう

が両立して、処理が不可能になっていた感じがします。。  
素直にN=100付近の数直線を書き、問題分に書かれた「100でちょうどD回割れる」の条件を満たす数に○でも打っていけばよかったと思います。