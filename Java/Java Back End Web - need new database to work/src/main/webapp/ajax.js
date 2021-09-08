function Register(){
    var username = document.getElementById('username').value;
    var email = document.getElementById('email').value;
    var pass = document.getElementById('pass').value;
    var cpass = document.getElementById('confpass').value;
    var fname = document.getElementById('fname').value;
    var lname = document.getElementById('lname').value;
    var birth = document.getElementById('birth').value;
    var radios  = document.getElementsByName('gender');
    var country = document.getElementById('country').value;
    var town = document.getElementById('town').value;
    var job = document.getElementById('job').value;
    var interests = document.getElementById('interests').value;
    var address = document.getElementById('address').value;
    var info = document.getElementById('info').value;
    var gender;
    
  
    for(var i=0;  i<radios.length; i++){
       if(radios[i].checked){
           gender = radios[i].value;
        }
    } 
    var xhr = new XMLHttpRequest();
    xhr.open('POST','Register');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};

    xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Username=' + username + '&Email=' + email + '&Password=' + pass + '&ConfirmPassword=' + cpass +
        '&FirstName=' + fname + '&Lastname=' + lname + '&Birth=' + birth + '&Gender=' + gender + '&Country=' + country + '&City=' + town + '&MoreInfo=' + info
        + '&ocupation=' + job + '&Address=' + address + '&Interests=' + interests);
   
    
    
}


function login() {
var username = document.getElementById('username').value;
var pass = document.getElementById('pass').value;  
   
var xhr = new XMLHttpRequest();
    xhr.open('POST','Login');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};

    xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Username=' + username + '&Pass=' + pass);


}

function Edit(){
    var username = document.getElementById('username').value;
    var email = document.getElementById('email').value;
    var pass = document.getElementById('pass').value;
    var cpass = document.getElementById('confpass').value;
    var fname = document.getElementById('fname').value;
    var lname = document.getElementById('lname').value;
    var birth = document.getElementById('birth').value;
    var radios  = document.getElementsByName('gender');
    var country = document.getElementById('country').value;
    var town = document.getElementById('town').value;
    var job = document.getElementById('job').value;
    var interests = document.getElementById('interests').value;
    var address = document.getElementById('address').value;
    var info = document.getElementById('info').value;
    var gender;
    
  
    for(var i=0;  i<radios.length; i++){
       if(radios[i].checked){
           gender = radios[i].value;
        }
    } 
    var xhr = new XMLHttpRequest();
    xhr.open('POST','EditUser');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};

    xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Username=' + username + '&Email=' + email + '&Password=' + pass + '&ConfirmPassword=' + cpass +
        '&FirstName=' + fname + '&Lastname=' + lname + '&Birth=' + birth + '&Gender=' + gender + '&Country=' + country + '&City=' + town + '&MoreInfo=' + info
        + '&ocupation=' + job + '&Address=' + address + '&Interests=' + interests);
   
    
    
}

function MyInfo(){

var xhr = new XMLHttpRequest();
    xhr.open('POST','ShowInfo');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};
xhr.send();
}

function AllUsers(){

var xhr = new XMLHttpRequest();
    xhr.open('POST','SeeAllUsers');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};
xhr.send();
}

function CreateInitiative(){
    
    var category = document.getElementById('category').value;
    var title = document.getElementById('title').value;
    var description = document.getElementById('description').value;
    var status = document.getElementById('status').value;
    var expire = document.getElementById('expire').value;
    
    var xhr = new XMLHttpRequest();
    xhr.open('POST','CreateInitiave');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};

xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Category=' + category + '&Title=' + title + '&Description=' + description +
        '&Status=' + status + '&Expire=' + expire);

}




function MyInitiatives(){

var xhr = new XMLHttpRequest();
    xhr.open('POST','MyInitiatives');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};
xhr.send();
}


function AddVote(){
    var initiativeID = document.getElementById('IniID').value;
    var user = document.getElementById('user').value;
    
    
    var xhr = new XMLHttpRequest();
    xhr.open('POST','addVote');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};

xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
xhr.send('Id=' + initiativeID + '&User=' + user);
        
    
}


function editInitiative(){
    var id = document.getElementById('IniID').value;
    var category = document.getElementById('category').value;
    var title = document.getElementById('title').value;
    var description = document.getElementById('description').value;
    var status = document.getElementById('status').value;
    var expire = document.getElementById('expire').value;
    
    var xhr = new XMLHttpRequest();
    xhr.open('POST','EditInitiative');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};

xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Category=' + category + '&Title=' + title + '&Description=' + description +
        '&Status=' + status + '&Id=' + id + '&Expire=' + expire);

}


function ActivePolicies(){

var xhr = new XMLHttpRequest();
    xhr.open('POST','ActivePolicies');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};
xhr.send();
}

function ShowVotes(){

var xhr = new XMLHttpRequest();
    xhr.open('POST','NewServlet');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};
xhr.send();
}

function Upvote(){

var id = document.getElementById('id').value;

var xhr = new XMLHttpRequest();
    xhr.open('POST','UpVote');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};


xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Id=' + id);

}


function ChangeVote(){

var id = document.getElementById('id').value;
var radios  = document.getElementsByName('vote');
var vote;

for(var i=0;  i<radios.length; i++){
       if(radios[i].checked){
           vote = radios[i].value;
        }
    } 


var xhr = new XMLHttpRequest();
    xhr.open('POST','ChangeVote');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};


xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Id=' + id + '&Vote=' + vote);

}

function EndedPolicies(){
    
var xhr = new XMLHttpRequest();
    xhr.open('POST','EndedPolicies');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};
xhr.send();
}


function DeletemySelf(){
    var xhr = new XMLHttpRequest();
    xhr.open('POST','DeleteMySelf');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};
xhr.send();
}

function ShowInitiative(){

var id = document.getElementById('id').value;

var xhr = new XMLHttpRequest();
    xhr.open('POST','showInitiative');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};


xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('Id=' + id);

}

function ShowUserInitiatives(){

var user = document.getElementById('user').value;

var xhr = new XMLHttpRequest();
    xhr.open('POST','ShowUserInitiative');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};


xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
    xhr.send('User=' + user);

}



function delegator(){

var user = document.getElementById('user').value;
var id = document.getElementById('id').value;

var xhr = new XMLHttpRequest();
    xhr.open('POST','Delegator');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};


xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
xhr.send('User=' + user + '&Id=' + id);

}

function DeleteNonPolicy(){

var id = document.getElementById('id').value;

var xhr = new XMLHttpRequest();
    xhr.open('POST','DeletenonPolicy');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};


xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
xhr.send('Id=' + id);

}



function rating(){

var user = document.getElementById('user').value;
var id = document.getElementById('id').value;
var rate = document.getElementById('rate').value;

var xhr = new XMLHttpRequest();
    xhr.open('POST','Rating');
   xhr.onload = function () {
if (xhr.readyState === 4 && xhr.status === 200) {
document.getElementById('ajaxContent').innerHTML = xhr.responseText;
} else if (xhr.status !== 200) {
alert('Request failed. Returned status of ' + xhr.status);
}
};


xhr.setRequestHeader('Content-type','application/x-www-form-urlencoded');
xhr.send('User=' + user + '&Id=' + id + '&Rate=' + rate);

}


