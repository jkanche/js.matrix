# Minimal example of using BioC classes in Webassembly

First run this to generate the WASM and JS module:

```sh
emcc --bind -I../libraries/tatami/include -std=c++1z target.cpp -o target.js
```

Then set up a local HTTP server:

```sh
python3 -m http.server
```

And open up `index.html`.
On the console you should see something like `"Matrix dimensions: 26 10"`.
