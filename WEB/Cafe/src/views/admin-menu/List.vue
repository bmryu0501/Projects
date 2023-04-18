<template>
<div>
    <div v-for="menu in menus"
    :key="menu.id"
    > 
        <div class="menu-container"
        @click="moveDetail(menu.id)">
            <!-- <div class="menu-image"
            :style="`background-image:url(${setImage(menu.image_src)})`"
            > -->
            <div class="menu-image">
                <img :src=setImage(menu.image_src) alt=menu.image_src>
            </div>
            <div class="menu-info-wrapper">
                <h2 class="menu-name">{{menu.name}}</h2>
                <p class="menu-description">{{menu.description}}</p>
            </div>
        </div>
    </div>

    <router-link to="/admin/menus/register">
        <b-button
        class="order-button w-100"
        variant="outline-dark"
        > 메뉴 추가하기
        </b-button>
    </router-link>
</div>
</template>

<script>
import {api} from "../../utils/api"

export default {
    data() {
        return {
            menus: []
        }
    },
    async created() {
        this.$store.commit("SET_TITLE", "메뉴 목록");
        const result = await api.menus.findAll();
        this.menus = result.data;
    },
    methods: {
        setImage(image_src) {
            return `http://ssafy-web.kro.kr:8080/${image_src}`
        },
        moveDetail(id) {
            this.$router.push(`/admin/menus/${id}`);
        }
    }
}
</script>

<style>
.menu-container {
  display: flex;
  align-items: center;
  border-bottom: 3px solid black;
}

.menu-info-wrapper {
  margin: 0 auto;
  text-align: center;
}

.menu-name {
  font-size: 25px;
  font-weight: bold;
}

.menu-description {
  padding-top: 10px;
}
.menu-image>img {
  width: 180px;
  height: 180px;
}
</style>