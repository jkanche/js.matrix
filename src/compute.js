// generate a matrix of size n by m
const n = 1000, m = 1000;
var matrix = [];

function getRandomArbitrary(max) {
    return Math.random() * max;
}

for (var i = 0; i < n; i++) {
    matrix[i] = new Uint16Array(m);
    matrix[i] = matrix[i].map(() => getRandomArbitrary(255));
}

// console.log(matrix);

function colSum(matrix, order) {

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
    
    console.log("##### COLSUM #####")
    console.log(colSum);
    return colSum;
}

function rowSum(matrix, order) {
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

    console.log("##### ROWSUM #####")
    console.log(rowSum);
    return rowSum
}

rowSum(matrix, order = [1,2,1,2]);
rowSum(matrix)
// console.log("after row sum")
colSum(matrix, order = [1,2,1,1]);
colSum(matrix);