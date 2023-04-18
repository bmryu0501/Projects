async function setRenderBackground() {
    const result = await axios.get("https://picsum.photos/1280/720", {responseType: 'blob'});
    
    const imageURL = URL.createObjectURL(result.data);
    document.querySelector('body').style.backgroundImage = `url(${imageURL})`;
}

function setTime() {
    const timer = document.querySelector('.timer');

    setInterval(() => {
        const date = new Date();
        timer.textContent = `${String(date.getHours()).padStart(2, '0')}:${String(date.getMinutes()).padStart(2, '0')}:${String(date.getSeconds()).padStart(2, '0')}`;
    }, 1000);
}

function setMemo() {
    const todo_list = JSON.parse(localStorage.getItem('todo'));

    if(todo_list) {
        const component = todo_list.reduce((acc, cur) => {
            acc += `<div class="memo">${cur}</div>`;
            return acc;
        }, "");

        document.querySelector('.memo-wrapper').insertAdjacentHTML('afterbegin', component);
    }
}

function addMemo(value) {
    let todo_list = JSON.parse(localStorage.getItem('todo'));
    if(!todo_list) todo_list = new Array();
    todo_list.push(value);
    localStorage.setItem('todo', JSON.stringify(todo_list));

    const component = `<div class="memo">${value}</div>`;

    document.querySelector('.memo-wrapper').insertAdjacentHTML('beforeend', component);
}

function renderTodo() {
    const memoInput = document.querySelector('.memo-input');
    setMemo();

    memoInput.addEventListener('keyup', function (e) {
        if(e.code === 'Enter' && e.target.value) {
            addMemo(e.target.value);

            memoInput.value = "";
        }
    })
}

function addClickEvent() {
    // 이벤트 위임
    document.addEventListener('click', function (e) {
        
        // Memo localStorage 제거
        if(e.target.classList.contains('memo')) {
            let todo_list = JSON.parse(localStorage.getItem('todo'));
            todo_list = todo_list.filter(element => element !== e.target.textContent);
            localStorage.setItem('todo', JSON.stringify(todo_list));

            e.target.textContent = "";
        }
    });
}




function getPosition(options) {
    // navigator.geolocation -> 일반 callback 함수(promise X)
    return new Promise((resolve, reject) => navigator.geolocation.getCurrentPosition(resolve, reject, options));
}

async function getWeather(latitude, longitude) {
    const Weather_API_KEY = '58ba8a9abc35eddb10183274379f9660'
    let weather_url;

    if(latitude && longitude) {
        weather_url = `https://api.openweathermap.org/data/2.5/forecast?lat=${latitude}&lon=${longitude}&appid=${Weather_API_KEY}`
    } else { // 위도 경도를 못받은 경우
        const city_name = 'Seoul';
        weather_url = `https://api.openweathermap.org/data/2.5/forecast?q=${city_name}&appid=${Weather_API_KEY}`
    }
    return await axios.get(weather_url);
}

function matchIcon(weatherData) {
    if (weatherData === "Clear") return "./images/039-sun.png";
    if (weatherData === "Clouds") return "./images/001-cloud.png";
    if (weatherData === "Rain") return "./images/003-rainy.png";
    if (weatherData === "Snow") return "./images/006-snowy.png";
    if (weatherData === "Thunderstorm") return "./images/008-storm.png";
    if (weatherData === "Drizzle") return "./images/031-snowflake.png";
    if (weatherData === "Atmosphere") return "./images/033-hurricane.png";
}

const changeToCelsius = (temp) => (temp - 273.15).toFixed(1);

function weatherWrapperComponent(e) {
    console.log(e)
    return `
    <div class="card flex-grow-1 m-2">
        <div class="card-header text-white text-center">
            ${e.dt_txt.split(' ')[0].split('-')[1]}월 ${e.dt_txt.split(' ')[0].split('-')[2]}일
        </div>
        <div class="card-body d-flex">
            <div class="flex-grow-1 d-flex flex-column justify-content-center align-items-center">
                <h5 class="card-title">${e.weather[0].main}</h5>
                <img class="weather-img" src='${matchIcon(e.weather[0].main)}'">
                <p class="card-text">${changeToCelsius(e.main.temp)}°C</p>
                <p class="card-text">최고 ${changeToCelsius(e.main.temp_max)}°C | 최저 ${changeToCelsius(e.main.temp_min)}°C</p>
            </div>
        </div>
    </div>
    `
}

async function renderWeather() {
    // getPosition 호출해서 위도 경도 받아옴
    let latitude = '';
    let longitude = '';
    try{
        const position = await getPosition();
        latitude = position.coords.latitude;
        longitude = position.coords.longitude;
    } catch (e){
        console.log(e);
    }
    const weatherResponse = await getWeather(latitude, longitude);
    const weatherData = weatherResponse.data;
    const weatherList = weatherData.list.reduce((acc, cur) => {
        if (cur.dt_txt.indexOf("18:00:00") > 0) {
            acc.push(cur);
        }
        return acc;
    }, []);
    const modalBody = document.querySelector(".modal-body");
    modalBody.innerHTML = weatherList.map(e => weatherWrapperComponent(e)).join("");
}

async function allRender() {
    setRenderBackground();
    setTime();
    renderTodo();
    addClickEvent();
    renderWeather();

    setInterval(() => {
        setRenderBackground();
    }, 5000);
}

allRender();