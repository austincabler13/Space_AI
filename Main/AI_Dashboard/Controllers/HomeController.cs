using Microsoft.AspNetCore.Mvc;

namespace AI_Dashboard.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index() => View();
        public IActionResult Connect() => View();
        public IActionResult Performance() => View();
        public IActionResult DamageReport() => View();
    }
}
