<template>
<div>
    <div v-for="order in orders"
    :key="order.id"
    > 
        <div class="order-container"
        @click="moveDetail(order.id)">
            <div class="order-info-wrapper">
                <h2 class="order-name">{{order.name}} {{order.quantity}} 잔</h2>
                <p class="order-description">{{order.request_detail}}</p>
            </div>
        </div>
    </div>

    <router-link to="/orders/register">
        <b-button
        class="order-button w-100"
        variant="outline-dark"
        > 주문하기
        </b-button>
    </router-link>
</div>
</template>

<script>
import {api} from "../../utils/api"

export default {
    data() {
        return {
            orders: []
        }
    },
    async created() {
        this.$store.commit("SET_TITLE", "주문 목록");
        const result = await api.orders.findAll();
        this.orders = result.data;
        console.log(result.data);
    },
    methods: {
        moveDetail(id) {
            this.$router.push(`/orders/list/${id}`);
        }
    }
}
</script>

<style>
.order-container {
  display: flex;
  align-items: center;
  border-bottom: 3px solid black;
}

.order-info-wrapper {
  margin: 0 auto;
  text-align: center;
}

.order-name {
  font-size: 25px;
  font-weight: bold;
}

.order-description {
  padding-top: 10px;
}
.order-image>img {
  width: 180px;
  height: 180px;
}
</style>