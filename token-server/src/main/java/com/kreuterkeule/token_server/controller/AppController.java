package com.kreuterkeule.token_server.controller;

import com.kreuterkeule.token_server.service.TokenService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;


@RestController
public class AppController {

    @Autowired
    private TokenService tokenService;

    @GetMapping("/")
    public String root() {
        return "success, server is running";
    }

    @GetMapping("/generateToken")
    public ResponseEntity<String> generateToken() {
        return new ResponseEntity<>(tokenService.generateToken(), HttpStatus.OK);
    }

    @GetMapping("/checkToken")
    public ResponseEntity<Boolean> checkToken(@RequestParam("token") String token) {
        return new ResponseEntity<>(tokenService.checkToken(token), HttpStatus.OK);
    }

    @GetMapping("/useToken")
    public ResponseEntity<Boolean> useToken(@RequestParam("token") String token) {
        return new ResponseEntity<>(tokenService.useToken(token), HttpStatus.OK);
    }
}
