<template>
  <div>
    <b-card
      v-if="data"
      :title="`${data.name} ${data.quantity}잔`"
      tag="article"
      class="mb-2 detail-card"
    >
      <b-card-text>
        {{data.request_detail}}
      </b-card-text>

      <b-button @click="moveRegister" href="#" variant="primary"
        >수정하기</b-button
      >
      <b-button @click="deleteOrder" href="#" variant="danger">삭제</b-button>
      <b-button @click="moveList" href="#" variant="outline-primary"
        >목록</b-button
      >
    </b-card>
  </div>
</template>

<script>
import { api } from "../../utils/api";
export default {
  data() {
    return {
      data: {},
    };
  },
  async created() {
    this.$store.commit("SET_TITLE", "상세 주문 내역");
    const result = await api.orders.findOne(this.$route.params.id);
    this.data = result.data[0];
    console.log(result.data[0]);
  },

  methods: {
    moveRegister() {
      this.$router.push(`/orders/register/${this.$route.params.id}`);
    },
    async deleteOrder() {
      const confirmResult = confirm("삭제하시겠습니까?");
      if (confirmResult) {
        const result = await api.orders.delete(this.$route.params.id);
        alert(result.data.message);
        this.$router.push("/orders/list");
      }
    },
    moveList() {
      this.$router.push("/orders/list");
    },
  },
};


</script>

<style>
</style>