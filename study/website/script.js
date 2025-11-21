
// Плавный скролл
document.addEventListener("DOMContentLoaded", function () {
    var scrollButtons = document.querySelectorAll('.nav-button');

    scrollButtons.forEach(function (button) {
        button.addEventListener('click', function (event) {
            event.preventDefault(); // Предотвращаем стандартное поведение ссылки
            var targetId = this.getAttribute('href').substring(1); // Получаем id целевого элемента
            var targetElement = document.getElementById(targetId);
            smoothScrollTo(targetElement);
        });
    });

    function smoothScrollTo(target) {
        var targetPosition = target.getBoundingClientRect().top + window.scrollY;
        var startPosition = window.scrollY;
        var distance = targetPosition - startPosition;
        var startTime = null;

        function animation(currentTime) {
            if (startTime === null) startTime = currentTime;
            var timeElapsed = currentTime - startTime;
            var progress = easeInOutQuad(timeElapsed, startPosition, distance, 1000);
            window.scrollTo(0, progress);
            if (timeElapsed < 1000) requestAnimationFrame(animation);
        }

        function easeInOutQuad(t, b, c, d) {
            t /= d / 2;
            if (t < 1) return c / 2 * t * t + b;
            t--;
            return -c / 2 * (t * (t - 2) - 1) + b;
        }

        requestAnimationFrame(animation);
    }
});


// Логика карусели
document.addEventListener("DOMContentLoaded", function () {
    const track = document.querySelector(".carousel .track");
    const items = document.querySelectorAll(".carousel .item");
    const prevButton = document.querySelector(".carousel .button-prev");
    const nextButton = document.querySelector(".carousel .button-next");

    let currentIndex = 0;

    function updateCarousel() {
        track.style.transform = `translateX(${-currentIndex * 100}%)`;
    }

    function goToNext() {
        currentIndex = (currentIndex + 1) % items.length;
        updateCarousel();
    }

    function goToPrev() {
        currentIndex = (currentIndex - 1 + items.length) % items.length;
        updateCarousel();
    }

    nextButton.addEventListener("click", goToNext);
    prevButton.addEventListener("click", goToPrev);
});

// Добавляем фон к каждой картинке
document.addEventListener("DOMContentLoaded", function () {
    // Получаем все элементы с классом .item
    var items = document.querySelectorAll(".workers .carousel .item .img-holder");

    // Проходим по каждому элементу и устанавливаем фон для ::before
    items.forEach(function (item) {
        var img = item.querySelector("img");

        // Устанавливаем фон для ::before равным изображению
        item.style.setProperty("--background-image", "url(" + img.src + ")");
    });
});


// проверка на корректность номера
function validateNumber() {
    var phoneNumberInput = document.getElementById("phoneNumber");
    var phoneNumber = phoneNumberInput.value;

    var phonePattern = /^\+\d{1,3}\d{10}$/;
    
    var errorIcon = document.querySelector(".error-icon");
    var notification = document.querySelector(".notification");
    var inputLine = document.querySelector(".input-line");

    if (phonePattern.test(phoneNumber)) {
        errorIcon.style.display = "none";
        notification.style.display = "block";
        phoneNumberInput.value = "";

        // Добавляем класс для анимации
        inputLine.classList.add("call-highlight");

        // Через 2 секунды убираем класс анимации
        setTimeout(function () {
            inputLine.classList.remove("call-highlight");
            notification.style.display = "none";
        }, 2000);

    } else {
        errorIcon.style.display = "inline-block";
    }
}
