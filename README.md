<h1>rizm</h1>

rizm is an interpreted programming language. The language is largely inspired by Python, both in terms of syntax and paradigms.

> The word "algorithm" is derived from the name "AlKhwarizmi". Latinized as "Algoritmi", which was later translated into English as "Algorithm" <br>


<br>
<br>


Examples
--------

#### "hello world"

<pre>
<i># simple "hello world" program</i>
<b>print</b>('hello world'); 
<b>print</b>("hello world"); <i># strings can be delimited by either " or '</i>
</pre>

#### Arithmetic

<pre>
<b>print</b>(((50 - 5*6)/4)**2);  <i># prints 25</i>
</pre>

#### `if` statements

<pre>
<b>int</b> b = 1;
<b>if</b>(b) {
    <b>print</b>("b is non-zero!");
} <b>else</b> {
    <b>print</b>("b is zero!");
}
</pre>

#### `while` statements

<pre>
<i># print integers from 1 to 9:</i>
<b>int</b> a = 1;
<b>while</b>(a < 10) {
    <b>print</b>(a);
    a += 1;
}
</pre>

#### `for` statements

<pre>
<i># equivalent of while-loop above:</i>
<b>for</b> a <b>in</b> (1:10) {  <i># range through integers from 1 to 9</i>
    <b>print</b>(a);
}
<b>for</b> a <b>in</b> (1:40:3) {  <i># range through integers from 1 to 40 with a step of 3</i>
    <b>print</b>(a);
}
</pre>

#### Functions

<pre>
<i># factorial function</i>
<b>def</b> fact(n) {
    <b>if</b>(n < 2) { <b>return</b> 1; } <b>else</b> { <b>return</b> n * fact(n - 1); }
}

<i># hypotenuse function</i>
<b>def</b> hypot(a, b) {
    <i># functions can be nested:</i>
    <b>def</b> square(x) {
        <b>return</b> x**2;
    }

    <i># functions can be anonymous:</i>
    <b>def int</b> sqrt = (: $1 ** 0.5);

    <b>return</b> sqrt(square(a) + square(b));
}
</pre>

#### `import` statements

<pre>
<i>#import other modules</i>
<b>import</b> 'module/utils';
</pre>
