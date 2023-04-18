<template>
  <div>
    <div class="form-wrapper">
      <div>메뉴 id: <input v-model="menus_id"></div>
      <div>메뉴 개수: <input v-model="quantity"></div>
      <div>주문 설명: <input v-model="request_detail"></div>
      <button v-if="$route.params.id" @click="update">메뉴 수정하기</button>
      <button v-else @click="create">메뉴 추가하기</button>
    </div>
  </div>
</template>

<script>
import {api} from "../../utils/api"

export default {
  data() {
    return {
      menus_id:0,
      quantity:1,
      request_detail: "",
    }
  },
  async created() {
    // 수정 모드는 this.$route.params.id가 존재한다.
    if(this.$route.params.id) {
      this.$store.commit("SET_TITLE", "주문 수정");
      const result = await api.orders.findOne(this.$route.params.id);
      console.log(result.data[0]);
      this.menus_id = result.data[0].menus_id;
      this.quantity = result.data[0].quantity;
      this.request_detail = result.data[0].request_detail;
    } else {
      this.$store.commit("SET_TITLE", "주문 추가");
    }
  },
  methods: {
    fileChange(e) {
      console.log(e);
      console.log(e.target.files);
      this.file = e.target.files[0];
    },
    setURL(file) {
      const imageURL = URL.createObjectURL(file);
      return imageURL;
    },
    async create() {
      if(!this.menus_id || !this.quantity || !this.request_detail) {
        alert("빈 정보를 입력해 주세요!");
        return;
      }

      const result = await api.orders.create(this.menus_id, this.quantity, this.request_detail);

      // result.data.success가 true인 경우에만 성공적으로 업로드
      if(result.data.success) {
        alert(result.data.message);
        this.$router.push("/orders/list");
      } else {
        alert(result.data.message);
      }
    },
    async update() {
      // update;
      const result = await api.orders.update(this.$route.params.id, this.menus_id, this.quantity, this.request_detail);
      console.log(result);
      alert(result.data.message);
      this.$router.push(`/orders/list/${this.$route.params.id}`)
    },
  }
}
</script>

<style>
.form-wrapper {
  display: flex;
  flex-direction: column;
  margin-top: 50px;
  border: 1px solid black;
  padding: 20px;
}

.form-wrapper > * {
  margin: 10px;
}

.image-wrapper {
  margin-top: 30px;
}
</style>