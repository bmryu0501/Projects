<template>
<div class="wrapper"
v-if="!$store.state.loading">
    <div class="img-wrapper">
        <img :src=result.image
        style="width:100px;height:100px">
    </div>
    
    <div>{{result.title}}</div>
    <div>{{result.price}}$</div>
    <div>{{result.description}}</div>
</div>
</template>

<script>
import {api} from "../../utils/api.js"

export default {
    data() {
        return {
            result: {}
        }
    },
    async created() {
        this.$store.commit("SET_LOADING", true);
        const result = await api.jsonplaceholder.findOne(this.$route.params.id);
        console.log(result.data);
        this.result = result.data;
        this.$store.commit("SET_LOADING", false);
    }
}
</script>

<style>
div{
    padding: 10px;
}
.wrapper{
    border: 1px solid black;
}
.img-wrapper{
    border: 1px solid black;
}
</style>