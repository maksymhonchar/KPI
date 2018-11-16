from flask import render_template, request, jsonify
from . import main


@main.app_errorhandler(403)
def forbidden(e):
    if request.accept_mimetypes.accept_json and \
            not request.accept_mimetypes.accept_html:
        response = jsonify({'error': 'forbidden'})
        response.status_code = 403
        return response
    return render_template(
        'error_page.html', code=403, short_msg='Forbidden', msg='Access denied, Forbidden'), 403


@main.app_errorhandler(404)
def page_not_found(e):
    if request.accept_mimetypes.accept_json and \
            not request.accept_mimetypes.accept_html:
        response = jsonify({'error': 'page not found'})
        response.status_code = 404
        return response
    return render_template(
        'error_page.html', code=404, short_msg='Not found', msg='Page Not Found'), 404


@main.app_errorhandler(413)
def request_entity_too_large(e):
    if request.accept_mimetypes.accept_json and \
            not request.accept_mimetypes.accept_html:
        response = jsonify({'error': 'request entity too large (more than 2 MB)'})
        response.status_code = 413
        return response
    return render_template(
        'error_page.html', code=413, short_msg='Request entity too large', msg='Capacity limit exceeded'), 413


@main.app_errorhandler(500)
def internal_server_error(e):
    if request.accept_mimetypes.accept_json and \
            not request.accept_mimetypes.accept_html:
        response = jsonify({'error': 'internal server error'})
        response.status_code = 500
        return response
    return render_template(
        'error_page.html', code=500, short_msg='Server error', msg='Internal Server Error'), 500
