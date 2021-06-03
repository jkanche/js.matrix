// generate a matrix of size n by m
const n = 10000, m = 10000;
var matrix = [];

function getRandomArbitrary() {
    return Math.random();
}

for (var i = 0; i < n; i++) {
    matrix[i] = new Float64Array(m);
    matrix[i] = matrix[i].map(() => getRandomArbitrary());
}

// console.log(matrix);

function colSum(matrix, order) {
    console.log("##### COLSUM #####");
    console.time("WHEE");
    var colSum;

    if (order) {
        var groups = order.filter((x, i, self) => self.indexOf(x) === i);
        colSum = [];
        groups.map((x,i) => {
            var indices = [];
            order.map((y ,j) => y == x ? indices.push(j) : false);
            if (indices.length == 1) {
                colSum.push(matrix.map(xm => xm[indices[0]]));
            } else {
                colSum.push(matrix.map((xm) => indices.map((jm) => xm[jm]).reduce((a,b) => a + b, 0)));
            }      
        })
    } else {
        colSum = matrix.reduce((x, y) => x.map((z, i) => z + y[i]));
    }
    console.timeEnd("WHEE");

    return colSum;
}

function rowSum(matrix, order) {
    console.log("##### COLSUM #####");
    console.time("WHEE");
    var rowSum;
    if (order) {
        var groups = order.filter((x, i, self) => self.indexOf(x) === i);
        rowSum = [];
        groups.map((x,i) => {
            var indices = [];
            order.map((y ,j) => y == x ? indices.push(j) : false);
            if (indices.length == 1) {
                rowSum.push(matrix[indices[0]]);
            } else {
                rowSum.push(indices.reduce((xi, yi) => matrix[xi].map((zi, zk) => zi + matrix[yi][zk])));
            }      
        })
    } else {
        rowSum = matrix.map(z => z.reduce((x, y) => x + y));
    }

    console.timeEnd("WHEE");
    return rowSum
}

rowSum(matrix)
// console.log("after row sum")
colSum(matrix);
