const key = '6a0e5029a4d71c44b52b4ae2b747bd1d';
const image_url = 'https://image.tmdb.org/t/p/original';
const num_movies = 16;

let count = 0;
const select = [];


async function getData() {
    const { data } = await axios.get('https://api.themoviedb.org/3/movie/now_playing', {
        params: {
            api_key: key,
            language: 'ko-KR'
        }
    });

    return data.results;
}


async function makeCardPool() {
    const data = await getData();

    const cardPool = data.reduce((acc, cur, idx) => {
        if (idx < num_movies) {
            acc.push({ id: cur.id, title: cur.title });
            acc.push({ id: cur.id, poster: cur.poster_path });
        }
        return acc;
    }, [])

    return cardPool;
}

function cardComponent(card) {
    if (card['title']) { // title의 경우
        return `
        <div class="flip">
            <div class="card">
                <div class="back"></div>
                <div class="front title id${card.id}" id="${card.id}">
                    ${card.title}
                </div>
            </div>
        </div>
        `
    } else { // poster의 경우
        const url = image_url + card.poster;
        return `
        <div class="flip">
            <div class="card">
                <div class="back"></div>
                <div class="front poster id${card.id}" id="${card.id}" style="background-image: url('${url}')"></div>
            </div>
        </div>
        `
    }
}

function displayCards(cards) {
    const components = cards.reduce((acc, cur) => {
        acc = acc + cardComponent(cur);
        return acc;
    }, "")

    document.querySelector('.frame').insertAdjacentHTML('afterbegin', components);
}

function clickCard(e) {
    e.target.parentElement.classList.add('flip_card');
    e.target.parentElement.children[1].classList.add('selected');

    select[count % 2] = e.target.parentElement.children[1];
    count++;

    if (count % 2 == 0) {
        let flag = true;

        document.querySelector('.trial').textContent = `trial: ${count / 2}`;

        if ((select[0].classList.contains('title') &&
            select[1].classList.contains('poster')) ||
            (select[1].classList.contains('title') &&
            select[0].classList.contains('poster'))) {
                if(select[0].id == select[1].id) { // 정답인 경우
                    flag = false;
                    setTimeout(() => {
                        document.querySelectorAll(`.id${select[0].id}`)[0].parentElement.parentElement.classList.add('hide');
                        document.querySelectorAll(`.id${select[0].id}`)[1].parentElement.parentElement.classList.add('hide');
                    }, 1000);
                }
            }
        if(flag) {
            document.querySelectorAll('.selected').forEach((i) => {
                setTimeout(() => {
                    i.classList.remove('selected');
                    i.parentElement.classList.remove('flip_card');
                }, 1000);
            });
        }
        
    }
}

async function main() {
    const cardPool = await makeCardPool();

    let cards = new Array(32);
    let it = num_movies * 2;
    while (it--) {
        let idx = Math.ceil(Math.random() * it);
        cards[it] = cardPool[idx];

        // swap
        let tmp = cardPool[idx];
        cardPool[idx] = cardPool[it];
        cardPool[it] = tmp;
    }

    console.log(cards);

    await displayCards(cards);

    const backs = document.querySelectorAll('.back');
    for (let i = 0; i < backs.length; i++) {
        backs[i].addEventListener('click', clickCard);
    }
}

main();

let time = 0;
setInterval(() => {
    time++;
    document.querySelector('.timer').textContent = `Time: ${time}`;
}, 1000);