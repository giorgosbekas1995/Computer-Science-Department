function ourMap(array) {
 // What we track
    var original = array, current;
    current = original;
    return function  mapWithCallback(fn, callback) {
 // If fn not a function return current Array
        if (typeof fn !== "function") {
            return current;
        }
 // Maping
        current = current.map(fn);
 // If callback is a function, execute callback
        if (typeof callback === "function") {
            callback.call(original, current);
        }
        return  mapWithCallback;
    }
}


// mapWithCallback can be used to repeatedly map a function to this input array
var mapWithCallback = ourMap([1, 2, 3]);

// call mapWithCallback to map squares to all numbers in [1, 2, 3]
mapWithCallback(function (elem) {
    return elem * elem; // return squares of numbers
  },

  function (array) {
  console.log('1. ' + this); // prints [1, 4, 9]
  console.log('2. ' + array); // prints [1, 2, 3]
});

// call mapWithCallback to get the cubes of elements. No callback used
mapWithCallback(function (elem) {
  return elem * elem * elem; // return cubes
});

// call mapWithCallback with no fn should return the current array
var currentArray = mapWithCallback(3);
console.log('3. currentArray', currentArray);   // prints [1, 64, 729]

// function 'what's the meaning?'
function wtm() {
  return;
}

var currentArray = ourMap([1, 2, 3])(wtm)();

// prints [undefined, undefined, undefined] since the fn returns undefined
console.log('4. currentArray', currentArray);

// Since mapWithCallback returns itself map calls can be chained like:
function square(elem) {
  return elem * elem;
}

function cube(elem) {
  return elem * elem * elem;
}

currentArray = ourMap([1, 2, 3])(square)(cube)();

// prints [1, 64, 729] since we map squares and then cubes
console.log('5. currentArray', currentArray);

// Multiple active ourMaps at the same time
var arrayMap1 = ourMap([1, 2, 3]);
var arrayMap2 = ourMap([4, 5, 6]);
console.log('6. ' + arrayMap1(square)());   // prints [1,4,9]
console.log('7. ' + arrayMap2(cube)());     // prints [64, 125, 216]
// Προσοχή αν τρέξετε console.log(array) πρέπει να πάρετε undefined
// Το ίδιο αν τρέξετε console.log(original) ή console.log(current)
//console.log(array);
//console.log(original);
//console.log(current);