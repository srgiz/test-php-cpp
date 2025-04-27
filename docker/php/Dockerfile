FROM php:8.2-fpm-alpine3.17

# docker exec -i -t cpp-php sh
# docker exec -i -t cpp-php bash

# base
RUN apk add --no-cache bash shadow git linux-headers

# cpp
RUN apk add --no-cache g++ make cmake pkgconfig

# INSTALL OPENCV https://docs.opencv.org/4.7.0/d7/d9f/tutorial_linux_install.html
RUN git clone --branch 4.7.0 https://github.com/opencv/opencv /tmp/opencv \
    && mkdir -p /tmp/opencv/build \
    && cd /tmp/opencv/build \
    && cmake /tmp/opencv -DOPENCV_GENERATE_PKGCONFIG=YES \
    && make -j4 \
    && make install \
    && rm -rf /tmp/opencv

# INSTALL PHP-CPP
RUN git clone --branch v3.0.0 https://github.com/fast-debug/PHP-CPP /tmp/php-cpp \
    && cd /tmp/php-cpp \
    && make \
    && make install \
    && rm -rf /tmp/php-cpp

# CUSTOM EXTENSION
COPY ./sld /tmp/sld
RUN cd /tmp/sld  \
    && make \
    && make install

# TEST GD
RUN apk add --no-cache zlib-dev libpng-dev jpeg-dev \
    && docker-php-ext-configure gd --with-jpeg \
    && docker-php-ext-install gd

WORKDIR /var/www
ENV DOCKER_APP_UID=1000
RUN usermod -u $DOCKER_APP_UID www-data
USER www-data
