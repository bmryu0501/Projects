<template>
<div class="list-wrapper-wrapper">
    <div
    v-for="list in lists"
    :key="list.id"
    @click="moveDetail(list.id)"
    class="list-wrapper">
    <div class="list">
    <img :src=list.image
    style="width:100px;height:100px">
    <div class="texts">{{list.title}}</div>
    </div>
    
    </div>
</div>
</template>

<script>
import {api} from "../../utils/api.js"

export default {
    data() {
        return {
            lists:[]
        }
    },
    async created() {
        this.$store.commit("SET_LOADING", true);
        const result = await api.jsonplaceholder.findAll();
        this.lists = result.data;
        this.$store.commit("SET_LOADING", false);
    },
    methods: {
        moveDetail(id) {
            this.$router.push(`/list/${id}`);
        }
    }
}
</script>

<style>
.list-wrapper{
    border: 1px solid black;
    padding: 10px;
}
.list-wrapper-wrapper{
    display: flex;
    flex-wrap: wrap;
    min-width: 500px;
}
.list{
    width: 200px;
    height: 300px;
}
.texts{
    padding-top: 30px;
    word-wrap: break-word;
}
</style>