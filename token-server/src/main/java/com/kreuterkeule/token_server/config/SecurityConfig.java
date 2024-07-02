package com.kreuterkeule.token_server.config;

import jakarta.servlet.FilterChain;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.Customizer;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.provisioning.InMemoryUserDetailsManager;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;

@EnableWebMvc
@EnableWebSecurity
@Configuration
public class SecurityConfig {

    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        return http.csrf(Customizer.withDefaults())
                .authorizeHttpRequests(request ->
                        request
                                .requestMatchers(
                                        "/checkToken",
                                        "/useToken"
                                ).permitAll()
                                .requestMatchers(
                                        "/generateToken"
                                ).hasRole("ADMIN")
                                .anyRequest().hasRole("ADMIN")
                )
                .httpBasic(Customizer.withDefaults()).build();

    }

    @Value("${spring.security.user.name}")
    private String defaultUsername;
    @Value("${spring.security.user.password}")
    private String defaultPassword;

    @Bean
    public UserDetailsService users() {
        UserDetails admin = User.builder()
                .username(defaultUsername)
                .password(passwordEncoder().encode(defaultPassword))
                .roles("USER", "ADMIN")
                .build();
        return new InMemoryUserDetailsManager(admin);
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }
}
