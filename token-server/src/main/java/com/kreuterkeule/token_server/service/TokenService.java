package com.kreuterkeule.token_server.service;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

@Service
public class TokenService {

    List<String> tokens = new ArrayList<>();

    public String generateToken() {
        String res = "";
        for (int i = 0; i < 4; i++) {
            Random random = new Random();
            int r = Math.abs(random.nextInt() % 10);
            res += r;
        }
        res = checkToken(res) ? generateToken() : res; // check if token exists already
        tokens.add(res);
        return res;
    }

    public boolean checkToken(String t) {
        return tokens.contains(t);
    }

    public boolean useToken(String t) {
        boolean res = tokens.contains(t);
        if (!res) return res;
        tokens.remove(t);
        return res;
    }


}
