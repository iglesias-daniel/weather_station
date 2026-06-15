idf_component_register(
    SRCS "main.c" "sensors.c" "espnow_tx.c"
    INCLUDE_DIRS "."
)

# Embed the ULP RISC-V program. Its exported symbols (pulse_count,
# wake_threshold) become available to main.c via the generated
# ulp_main.h header.
set(ulp_app_name ulp_main)
set(ulp_sources "${CMAKE_CURRENT_SOURCE_DIR}/ulp/ulp_main.c")
set(ulp_exp_dep_srcs "main.c")

ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}")
