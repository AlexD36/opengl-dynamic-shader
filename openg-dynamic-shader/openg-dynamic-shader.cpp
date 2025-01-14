#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// Screen dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Global variables for interaction
float zoomFactor = 1.0f;
float durationFactor = 4.0f;
float powerFactor = 0.51f;

// Shader source
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
out vec2 TexCoord;
void main() {
    gl_Position = vec4(aPos, 1.0);
    TexCoord = (aPos.xy + vec2(1.0)) * 0.5; // Map [-1,1] to [0,1]
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform float iTime;
uniform vec2 iResolution;
uniform vec4 iMouse;
uniform float zoomFactor;
uniform float durationFactor;
uniform float powerFactor;

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    float t = iTime + 5.0;
    float z = zoomFactor;

    const int n = 100; // particle count
    vec3 startColor = vec3(0.5 + 0.5 * sin(iTime * 0.5), 0.5 + 0.5 * sin(iTime * 0.7), 0.5 + 0.5 * sin(iTime * 0.9));
    vec3 endColor = vec3(0.5 + 0.5 * sin(iTime * 0.3), 0.5 + 0.5 * sin(iTime * 0.6), 0.5 + 0.5 * sin(iTime * 0.8));

    float startRadius = 0.84;
    float endRadius = 1.6;

    float power = powerFactor;
    float duration = durationFactor;

    vec2 s = iResolution.xy;
    vec2 v = z * (2.0 * fragCoord - s) / s.y;

    if (iMouse.z > 0.0) v *= iMouse.y / s.y * 20.0;
    if (iMouse.z > 0.0) duration = iMouse.x / s.x * 10.0;

    vec3 col = vec3(0.0);

    vec2 pm = v.yx * 2.8;
    float dMax = duration;

    float evo = (sin(iTime * 0.01 + 400.0) * 0.5 + 0.5) * 99.0 + 1.0;
    float mb = 0.0;
    float mbRadius = 0.0;
    float sum = 0.0;

    for (int i = 0; i < n; i++) {
        float d = fract(t * power + 48934.4238 * sin(float(i / int(evo)) * 692.7398));
        float a = 6.28 * float(i) / float(n);
        float x = d * cos(a) * duration;
        float y = d * sin(a) * duration;

        float distRatio = d / dMax;
        mbRadius = mix(startRadius, endRadius, distRatio);

        vec2 p = v - vec2(x, y);
        mb = mbRadius / dot(p, p);

        sum += mb;
        col = mix(col, mix(startColor, endColor, distRatio), mb / sum);
    }

    sum /= float(n);
    col = normalize(col) * sum;
    sum = clamp(sum, 0.0, 0.4);

    vec3 tex = vec3(1.0);
    col *= smoothstep(tex, vec3(0.0), vec3(sum));

    fragColor.rgb = col;
}

void main() {
    mainImage(FragColor, TexCoord * iResolution);
}
)";

// Key callback to adjust parameters
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_UP:
            zoomFactor += 0.1f;
            break;
        case GLFW_KEY_DOWN:
            zoomFactor -= 0.1f;
            break;
        case GLFW_KEY_LEFT:
            powerFactor -= 0.01f;
            break;
        case GLFW_KEY_RIGHT:
            powerFactor += 0.01f;
            break;
        case GLFW_KEY_W:
            durationFactor += 0.1f;
            break;
        case GLFW_KEY_S:
            durationFactor -= 0.1f;
            break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dynamic OpenGL Shader", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // Setup key callback
    glfwSetKeyCallback(window, keyCallback);

    // Compile and link shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Cleanup shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glUniform1f(glGetUniformLocation(shaderProgram, "iTime"), (float)glfwGetTime());
        glUniform2f(glGetUniformLocation(shaderProgram, "iResolution"), WIDTH, HEIGHT);
        glUniform1f(glGetUniformLocation(shaderProgram, "zoomFactor"), zoomFactor);
        glUniform1f(glGetUniformLocation(shaderProgram, "durationFactor"), durationFactor);
        glUniform1f(glGetUniformLocation(shaderProgram, "powerFactor"), powerFactor);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
