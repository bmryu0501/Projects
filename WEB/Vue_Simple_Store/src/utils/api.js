import axios from "axios";

// request로 요청 시 기본적으로 base url을 넣고 시작
const request = axios.create({
    baseURL: "https://fakestoreapi.com/"
})

export const api = {
    jsonplaceholder: {
        findAll:() => request.get("/products"),
        findOne:(id) => request.get(`/products/${id}`)
    }
}